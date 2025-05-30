#include<mpi.h>
#include<stdio.h>
int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank, size,array_size=16;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size > array_size)
    {
        if (rank == 0)
        {
            printf("number of processors must be less than array or buffer size");
        }
        MPI_Finalize();
        return 1;
    }
    
    int chunk_size = array_size / size;

    if (rank == 0){
        int buffer[array_size];
        
        for (int i = 0; i < array_size; i++)
        {
            buffer[i] = i+1;
        }
        
        MPI_Request send_reqs[size - 1];

        for (int i = 1; i < size; i++)
        {
            MPI_Isend(&buffer[i * chunk_size], chunk_size, MPI_INT, i, 0, MPI_COMM_WORLD, &send_reqs[i - 1]);
        }
        

        for (int i = 0; i < chunk_size; i++)
        {
            buffer[i] *= buffer[i];
        }

        MPI_Request rcv_reqs[size - 1];
        for (int i = 0; i < size; i++)
        {
            MPI_Irecv(&buffer[i * chunk_size], chunk_size, MPI_INT, i, 1, MPI_COMM_WORLD, &rcv_reqs[i - 1]);
        }
        
        
        for (int i = 0; i < array_size; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }
    else{
        int sub_array[array_size];
        MPI_Request wrk_reqs[2];

        MPI_Irecv(sub_array, chunk_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &wrk_reqs[0]);
        

        for (int i = 0; i < chunk_size; i++)
        {
            sub_array[i] *= sub_array[i];
        }
        
        MPI_Isend(sub_array, chunk_size, MPI_INT, 0, 1, MPI_COMM_WORLD, &wrk_reqs[1]);
        
    }
    MPI_Finalize();
    return 0;
}