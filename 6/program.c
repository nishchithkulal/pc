#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, data = 10;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Process %d sending first\n", rank);
        MPI_Send(&rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received first element %d\n", rank, data);
    } else {
        printf("Process %d sending first\n", rank);
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process %d received first element %d\n", rank, data);
    }

    MPI_Finalize();
    return 0;
}
