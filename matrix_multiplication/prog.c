#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int p, q, m, n;

    do
    {
        printf("\nEnter dimension of Matrix 1: ");
        scanf("%d%d", &p, &q);

        printf("\nEnter dimension of Matrix 1: ");
        scanf("%d%d", &m, &n);
    } while (q != m);

    int *arr1[p], *arr2[m];

    for (int i = 0; i < p; i++)
    {
        arr1[i] = (int *)malloc(q * sizeof(int));
    }

    for (int i = 0; i < m; i++)
    {
        arr2[i] = (int *)malloc(n * sizeof(int));
    }

    int *result[p];
    for (int i = 0; i < p; i++)
    {
        result[i] = (int *)malloc(n * sizeof(int));
    }

    for (int t = 1; t <= 8; t *= 2)
    {
        int i,j,k;
        double t1=omp_get_wtime();
        omp_set_num_threads(t);
        #pragma omp parallel for private(j,k)
        for ( i = 0; i < p; i++)
        {
            for ( j = 0; j < n; j++)
            {
                result[i][j] = 0;

                for ( k = 0; k < q; k++)
                {
                    result[i][j] += arr1[i][k] * arr2[k][j];
                }
            }
        }
        double t2=omp_get_wtime();

        printf("Size = %d, threads = %d, time=%lf\n",p,t,t2-t1);
    }
}