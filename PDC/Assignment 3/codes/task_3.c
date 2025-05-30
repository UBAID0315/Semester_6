#include<stdio.h>
#include<time.h>
#include<mpi.h>
#include <stdlib.h>

int main(int argc, char** argv){
    MPI_Init(&argc,&argv);  // Initialize MPI

    int rank,size;          // Neccessary Variables
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);    // rank and size declaration
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    int buffer[size];           // data storage area
    srand(time(NULL)+rank);     // for taking each time different random value
    int value = rand() % 101;   // random value from 1-100
    int temp;
    
    MPI_Allgather(&value, 1, MPI_INT, buffer, 1, MPI_INT, MPI_COMM_WORLD); // Gather to collect all values from the processes

    MPI_Reduce(&value, &temp, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);// Collect and apply max function on those values
    
    // Just for displaying values by Master
    if (rank == 0)
    {        
        for (int i = 0; i < size; i++)
        {        
            printf("%d ",buffer[i]);
        }
        printf("\n");        
        printf("Maximum value: %d \n",temp);
    }
    
    // For End-up MPI
    MPI_Finalize();
    return 0;
}