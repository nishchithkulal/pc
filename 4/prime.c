#include <stdio.h>
#include <omp.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int count = 0;
    int n = 10000;
    #pragma omp parallel for reduction(+:count)
    for (int i = 2; i <= n; i++)
        if (isPrime(i)) count++;
    printf("Number of primes = %d\n", count);
    return 0;
}
