#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, data = 100;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    else MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d has data %d\n", rank, data);
    MPI_Finalize();
    return 0;
}
