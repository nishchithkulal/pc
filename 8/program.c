#include <mpi.h>
#include <stdio.h>

int main() {
    int rank, size;
    int send_data[4];
    int recv_data;
    int gathered_data[4];

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < 4; i++) 
            send_data[i] = (i + 1) * 10;
        printf("Process 0 scatters the following data ");
        for (int i = 0; i < 4; i++) 
            printf("%d ", send_data[i]);
    }

    MPI_Scatter(send_data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf(" \nProcess %d received number %d\n", rank, recv_data);
    fflush(stdout);
    recv_data *= 2;
    MPI_Gather(&recv_data, 1, MPI_INT, gathered_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
    	printf("\n\nFinal gathered data: ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", gathered_data[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
