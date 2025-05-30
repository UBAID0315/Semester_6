#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){    // passing arguments while exection
    MPI_Init(NULL,NULL);            // initialize MPI environment

    int rank,data;                  // neccessary variables

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // comm_rank to give each process unique rank

    if(rank == 0){                  // Master process initialize data variable
        data = 10;
    }
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);    // Broadcasting of data to other processes
    printf("value on %d: after recieved: %d\n", rank, data); // Display the results over all processes

    MPI_Finalize();                 // Close the MPI environment before exit
    return 0;
}