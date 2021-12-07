#include <stdio.h>
#include <stdlib.h>
#include <gd.h>
#include <omp.h>
#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;
double t = 0.0;

long strike(bool composite[], long start, long incr, long end)
{
    long i;
    for (i = start; i <= end; i += incr)
        composite[i] = true;

    return i;
}

long cacheUnfriendlySieve(long n)
{
    long count = 0;
    long m = (long)sqrt((double)n);
    bool *composite = new bool[n + 1];
    memset(composite, 0, n);
    t = omp_get_wtime();
    for (long i = 2; i <= m; i++)
    {
        if (!composite[i])
        {
            count++;
            strike(composite, 2 * i, i, n);
        }
    }

    for (long i = m + 1; i <= n; i++)
    {
        if (!composite[i])
        {
            count++;
        }
    }

    t = omp_get_wtime() - t;
    delete[] composite;
    return count;
}

long cacheFriendlySieve(long n)
{
    long count = 0;
    long m = (long)sqrt((double)n);

    bool *composite = new bool[n + 1];
    memset(composite, 0, n);
    long *factor = new long[m];
    long *striker = new long[m];
    long n_factor = 0;

    t = omp_get_wtime();

    for (long i = 2; i <= m; i++)
    {
        if (!composite[i])
        {
            count++;
            striker[n_factor] = strike(composite, 2 * i, i, m);
            factor[n_factor] = i;
            n_factor++;
        }
    }

    for (long window = m + 1; window <= n; window += m)
    {
        long limit = min(window + m - 1, n);

        for (long k = 0; k < n_factor; k++)
        {
            striker[k] = strike(composite, striker[k], factor[k], limit);
        }

        for (long i = window; i <= limit; i++)
        {
            if (!composite[i])
            {
                count++;
            }
        }
    }

    t = omp_get_wtime() - t;

    delete[] composite;
    delete[] factor;
    delete[] striker;

    return count;
}

long parallelSieve(long n)
{
    long count = 0;
    long m = (long)sqrt((double)n);
    long n_factor = 0;
    long *factor = new long[m];
    t=omp_get_wtime();
#pragma omp parallel
    {
        bool *composite = new bool[m + 1];
        long *striker = new long[m];

#pragma omp single
        {

            memset(composite, 0, m);

            for (long i = 2; i <= m; i++)
            {
                if (!composite[i])
                {
                    count++;
                    strike(composite, 2 * i, i, m);
                    factor[n_factor] = i;
                    n_factor++;
                }
            }
        }

        long base = -1;

#pragma omp for reduction(+ \
                          : count)

        for (long window = m + 1; window <= n; window += m)
        {
            memset(composite, 0, m);

            if (base != window)
            {
                base = window;

                for (long k = 0; k < n_factor; k++)
                {
                    striker[k] = (base + factor[k] - 1) / factor[k] * factor[k] - base;
                }
            }

            long limit = min(window + m - 1, n) - base;

            for (long k = 0; k < n_factor; k++)
            {
                striker[k] = strike(composite, striker[k], factor[k], limit) - m;
            }

            for (long i = 0; i <= limit; i++)
            {
                if (!composite[i])
                {
                    count++;
                }
            }

            base += m;
        }

        delete[] composite;
        delete[] striker;
    }

    t = omp_get_wtime() - t;
    delete[] factor;

    return count;
}

int main()
{
    cout << "Unfriendly: " << cacheUnfriendlySieve(10000000) << endl;
    cout << "Time: " << t << endl;
    cout << "friendly: " << cacheFriendlySieve(10000000) << endl;
    cout << "Time: " << t << endl;
    cout << "Parallel: " << parallelSieve(10000000) << endl;
    cout << "Time: " << t << endl;

    return 0;
}
