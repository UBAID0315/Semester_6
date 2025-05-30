#include<stdio.h>
#include<mpi.h>
int main(int argc, char** argv){

    MPI_Init(&argc,&argv);                  // Initialize MPI
    int rank,array_size = 16,size;          // Neccessary Variables
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // rank and size(no of processors)
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int snd_buffer[array_size],rcv_buffer[array_size/size]; // buffers (data storage)
    int chunk_size = array_size / size;     // 4

    if(rank == 0){
        // Initialization of array from Master
        for(int i = 0; i < array_size; i++){
            snd_buffer[i] = i+1;
        }
    }
    
    // Scatter the data among processors and 
    MPI_Scatter(snd_buffer, chunk_size, MPI_INT ,rcv_buffer, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < chunk_size; i++)
    {
        // Multipltication of values by 2
        rcv_buffer[i] *= 2;
    }
    
    // Gather all values and store back into snd_buffer
    MPI_Gather(rcv_buffer, chunk_size, MPI_INT, snd_buffer, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Display values using Master
    if (rank == 0)
    {
        for (int i = 0; i < array_size; i++)
        {            
            printf("%d ",snd_buffer[i]);
        }
        printf("\n");        
    }
    
    MPI_Finalize();
    return 0;
}