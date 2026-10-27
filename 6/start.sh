mpicc deadlock.c -o deadlock
mpiexec -np 2 ./deadlock
