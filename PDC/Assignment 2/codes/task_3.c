#include<mpi.h>
#include<stdio.h>
int main(int argc, char** argv){

    MPI_Init(&argc, &argv);

    int rank,size,array_size=16;

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

    if (rank == 0){
        int buffer1[array_size];
        int buffer2[array_size];

        for (int i = 0; i < array_size; i++)
        {
            buffer1[i] = i+1;
            buffer2[i] = i+1;
        }
        
        MPI_Request snd_req[2];
        MPI_Status snd_status[2];
        MPI_Isend(&buffer1, array_size, MPI_INT, 1,0, MPI_COMM_WORLD, &snd_req[0]);
        MPI_Wait(&snd_req[0], &snd_status[0]);

        MPI_Isend(&buffer2, array_size, MPI_INT, 2,1, MPI_COMM_WORLD, &snd_req[1]);
        MPI_Wait(&snd_req[1], &snd_status[1]);
    }
    else if (rank > 0 && rank <= 2)
    {
        int sub_array1[array_size], sub_array2[array_size];
        MPI_Request wrk_reqs[2];
        MPI_Status status[2];

        if (rank == 1)
        {
            MPI_Irecv(sub_array1, array_size, MPI_INT, 0,0, MPI_COMM_WORLD, &wrk_reqs[0]);
            MPI_Wait(&wrk_reqs[0], &status[0]);
        }
        else if (rank == 2)
        {
            MPI_Irecv(sub_array2, array_size, MPI_INT, 0,1, MPI_COMM_WORLD, &wrk_reqs[1]);
            MPI_Wait(&wrk_reqs[1], &status[1]);
        }

        for (int i = 0; i < array_size; i++)
        {
            sub_array1[i] *= sub_array1[i];
            sub_array2[i] *= sub_array2[i];
        }

        MPI_Request snd_req[2];
        MPI_Status wrk_status[2];
        if (rank == 1)
        {
            MPI_Isend(&sub_array1, array_size, MPI_INT, 3,2, MPI_COMM_WORLD, &snd_req[0]);
            MPI_Wait(&snd_req[0], &wrk_status[0]);
        }
        else{
            MPI_Isend(&sub_array2, array_size, MPI_INT, 3,3, MPI_COMM_WORLD, &snd_req[1]);        
            MPI_Wait(&snd_req[1], &wrk_status[1]);
        }
    }
    else{
        int temp[array_size * 2];
        MPI_Request rq[2];
        MPI_Status status[2];

        MPI_Irecv(&temp[0], array_size, MPI_INT, 1,2, MPI_COMM_WORLD, &rq[0]);
        MPI_Wait(&rq[0], &status[0]);

        MPI_Irecv(&temp[array_size], array_size, MPI_INT, 2,3, MPI_COMM_WORLD, &rq[1]);
        MPI_Wait(&rq[1], &status[1]);

        printf("Final Results:\n");
        for (int i = 0; i < array_size*2; i++)
        {
            printf("%d ",temp[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}