
#include <stdio.h>
#include <omp.h>

int fib(int n) {
    int x, y;
    if (n < 2) return n;
    #pragma omp task shared(x)
    x = fib(n - 1);
    #pragma omp task shared(y)
    y = fib(n - 2);
    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 4;
    int result;
    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    printf("Fib(%d) = %d\n", n, result);
    return 0;
}
