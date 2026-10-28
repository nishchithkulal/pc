
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define THRESHOLD 50000

void merge(int arr[], int l, int m, int r, int temp[]) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = temp[i];
}

void mergeSortSeq(int arr[], int l, int r, int temp[]) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSeq(arr, l, m, temp);
        mergeSortSeq(arr, m + 1, r, temp);
        merge(arr, l, m, r, temp);
    }
}

void mergeSortPar(int arr[], int l, int r, int temp[], int depth) {
    if (r - l + 1 <= THRESHOLD) { mergeSortSeq(arr, l, r, temp); return; }
    if (l < r) {
        int m = l + (r - l) / 2;
        if (depth > 0) {
            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortPar(arr, l, m, temp, depth - 1);
                #pragma omp section
                mergeSortPar(arr, m + 1, r, temp, depth - 1);
            }
        } else {
            mergeSortPar(arr, l, m, temp, 0);
            mergeSortPar(arr, m + 1, r, temp, 0);
        }
        merge(arr, l, m, r, temp);
    }
}

int main() {	
    omp_set_nested(1);
    omp_set_num_threads(8);

    int n = 1000000;
    int *arr = malloc(n * sizeof(int));
    int *arrSeq = malloc(n * sizeof(int));
    int *temp = malloc(n * sizeof(int));
    int *tempSeq = malloc(n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) arrSeq[i] = arr[i] = rand();

    double startSeq = omp_get_wtime();
    mergeSortSeq(arrSeq, 0, n - 1, tempSeq);
    printf("Time taken by sequential merge sort: %f seconds\n", omp_get_wtime() - startSeq);

    double startPar = omp_get_wtime();
    #pragma omp parallel
    #pragma omp single
    mergeSortPar(arr, 0, n - 1, temp, 3);
    printf("Time taken by parallel merge sort: %f seconds\n", omp_get_wtime() - startPar);

    free(arr); free(arrSeq); free(temp); free(tempSeq);
    return 0;
}
