#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);                        // Initialize the MPI
    int rank,size,array_size=16;                   // Neccessary variables
    
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);          // Specify ranks and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (size > array_size)                         // Check (processors < array_size)
    {
        if (rank == 0)
        {
            printf("Error! Processors size:%d must be less than array size: %d",size,array_size);        
        }
        
        MPI_Finalize();
        return 1;
    }
    
    int chunk_size = array_size / size;            // Logic to find chunksize for data distributions
    
    if (rank == 0)                                 // Distributes data using Master Process
    {
        int buffer[array_size];                    // Initialize buffer or storage
        
        for (int i = 0; i < 16; i++)               // Stores values in array
        {
            buffer[i] = i+1;
        }        

        for (int i = 1; i < size; i++)             // Sending chunks to the other processes
        {
            MPI_Send(&buffer[i * chunk_size], chunk_size, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        
        // Taking Square of array value (1-4) i.e chunksize = 4
        for (int i = 0; i < chunk_size; i++)
        {
            buffer[i] = buffer[i]*buffer[i];
        }
        
        // Receiving the work done by other processes
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&buffer[i*chunk_size], chunk_size, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Display the combined result using Master
        for (int i = 0; i < array_size; i++) {
            printf("%d ", buffer[i]);
        }
        printf("\n");
        
    }
    else
    {
        int sub_array[array_size];      // take an array to store the receiving data
        MPI_Recv(sub_array, chunk_size, MPI_INT, 0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receiving the chunks from Master

        // Squaring
        for (int i = 0; i < chunk_size; i++)
        {
            sub_array[i] *= sub_array[i];
        }
        // Again send back result to Master
        MPI_Send(sub_array, chunk_size, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}