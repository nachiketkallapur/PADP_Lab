#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

#define BUFFER_SIZE 32

int main(int argc, char *argv[]){

    int rank,numprocs;
    int root=0,tag=0;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    char message[BUFFER_SIZE];

    if(rank>0){
        strcpy(message,"HELLO! RVCE");
        MPI_Send(message,BUFFER_SIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD);
    }

    if(rank==0){
        MPI_Status status;
        for(int i=1;i<4;i++){
            MPI_Recv(message,BUFFER_SIZE,MPI_CHAR,i,tag,MPI_COMM_WORLD,&status);
            printf("In process %d, received %s from process %d\n",rank,message,i);
        }
    }

    MPI_Finalize();

    return 0;
}