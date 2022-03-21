#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[]){

    int rank;
    double x,y,z,pi,t;
    int count=0,reduced_count;
    int iter=10000000,reduced_iter;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0){
        t=MPI_Wtime();
    }

    if(rank>0){
        srand(734896);
        for(int i=0;i<iter;i++){
            x=(double)rand()/RAND_MAX;
            y=(double)rand()/RAND_MAX;
            z=x*x+y*y;

            if(z<=1) count++;
        }
    }

    MPI_Reduce(&count,&reduced_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&iter,&reduced_iter,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    reduced_iter=reduced_iter-iter;

    if(rank==0){
        t=MPI_Wtime()-t;
        pi=(double)reduced_count/reduced_iter*4;

        printf("PI = %lf, time = %lf\n",pi,t);
    }

    MPI_Finalize();
    
    return 0;
}