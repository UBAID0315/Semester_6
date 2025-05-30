#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, cycles = 4;
    int count = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        count = 1;
        MPI_Send(&count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        for (int i = 1; i < cycles; i++)
        {
            MPI_Recv(&count, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count += 1;
            MPI_Send(&count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }

        MPI_Recv(&count, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Final Count: %d\n", count);
    }
    else if (rank == 1)
    {
        for (int i = 0; i < cycles; i++)
        {
            MPI_Recv(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count += 1;
            MPI_Send(&count, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        }
    }
    else if (rank == 2)
    {
        for (int i = 0; i < cycles; i++)
        {
            MPI_Recv(&count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count += 1;
            MPI_Send(&count, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
        }
    }
    else if (rank == 3)
    {
        for (int i = 0; i < cycles; i++)
        {
            MPI_Recv(&count, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count += 1;
            MPI_Send(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
