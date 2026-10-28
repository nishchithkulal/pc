mpicc sendrecv.c -o sendrecv
mpiexec -np 2 ./sendrecv
