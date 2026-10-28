mpicc bcast.c -o bcast
mpiexec -np 4 ./bcast
