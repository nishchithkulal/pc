#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    #pragma omp parallel for schedule(static,2)
    for (i = 0; i < 8; i++) {
        printf("Thread %d executes iteration %d\n", omp_get_thread_num(), i);
    }
    return 0;
}
