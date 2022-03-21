#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    double x,y,z,pi;
    srand(734896);

    for(int t=1;t<=8;t*=2){

        for(int n=10000;n<=50000;n+=10000){
            int count=0;

            double t1=omp_get_wtime();
            omp_set_num_threads(t);

            #pragma omp parallel for
            for(int i=0;i<n;i++){
                x=(double)rand()/RAND_MAX;
                y=(double)rand()/RAND_MAX;
                z=x*x+y*y;

                if(z<=1) count++;
            }

            pi=(double)count/n*4;

            double t2=omp_get_wtime();
            printf("\nThreads: %d, Trials: %d, PI: %lf, time: %lf",t,n,pi,t2-t1);
        }
        printf("\n");
    }

    
}