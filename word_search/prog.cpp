#include <iostream>
#include <fstream>
#include <cstring>
#include <omp.h>
using namespace std;

string inputfile = "words.txt";
string words[3] = {"Hello", "hye", "rv"};

int main()
{
    double time;

    for (int t = 1; t <= 8; t *= 2)
    {
        time = omp_get_wtime();
        omp_set_num_threads(t);
#pragma omp parallel for
        for (int i = 0; i < 3; i++)
        {
            int count = 0;
            string word;
            fstream file;
            file.open(inputfile.c_str());
            while (file >> word)
            {
                if (strcmp(words[i].c_str(), word.c_str()) == 0)
                {
                    count++;
                }
            }
            cout << words[i] << " occuring " << count << endl;
        }
        time = omp_get_wtime() - time;
        cout << "Threads " << t << " time taken = " << time << endl<<endl;
    }

    return 0;
}
