mpicc scatter_gather.c -o scatter_gather
mpiexec -np 4 ./scatter_gather
