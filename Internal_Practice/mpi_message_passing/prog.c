#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>


#define BUFFER_SIZE 32

int main(int argc, char *argv[]){
    int root=0,tag=0;
    MPI_Init(&argc,&argv);
    int rank, numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    char message[BUFFER_SIZE];
    MPI_Status status;
    if(rank==0){
        system("hostname");
        strcpy(message,"Hello India!");

        for(int i=1;i<numprocs;i++){
            MPI_Send(message,BUFFER_SIZE,MPI_CHAR,i,tag,MPI_COMM_WORLD);
        }
    }

    else {
        system("hostname");
        MPI_Recv(message,BUFFER_SIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD,&status);

        printf("\n%s received from process with rank %d from process with rank %d\n",message,rank,root);
    }

    MPI_Finalize();

    return 0;
}