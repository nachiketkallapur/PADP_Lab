#include<iostream>
#include<fstream>
#include<cstring>
#include<omp.h>

using namespace std;
string filename="p.txt";
string words[4]={"aaa","p","q","aa"};
int main()
{
    double t;
    for(int i=1;i<=8;i=i*2){
        t=omp_get_wtime();
        #pragma omp parallel for
        for(int j=0;j<4;j++)
        {
            fstream file;
            file.open(filename.c_str());
            string word;
            int count=0;
            while(file>>word)
            {
                if(strcmp(words[j].c_str(),word.c_str())==0)
                count++;
            }
            cout<<words[j]<<":"<<count<<endl;
        }
        cout<<"Thread:"<<i<<"\tTime:"<<omp_get_wtime()-t<<endl;
    }
    return 0;
}