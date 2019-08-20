#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "scimath.h"

#define SIZE 100000000

ksm_GENERIC_MAX(int)

double times_2(double x) {
    return x * 2;
}

double my_func(double x) {
    return pow(x, 3);
}

int main() {
    double x = 5.0;
    double *arr1 = malloc(sizeof(double) * SIZE);
    double *arr2 = malloc(sizeof(double) * SIZE);
    size_t i;
    int maximum;
    unsigned long runtime;

    printf("f'(x) = %f\n", ksm_first_deriv(my_func, x));
    printf("f''(x) = %f\n", ksm_second_deriv(my_func, x));
    
    for (i = 0; i < SIZE; i++) {
        arr1[i] = i;
    }


    ksm_TIMEIT(ksm_map(sqrt, arr2, arr1, SIZE), &runtime);
    printf("ksm_map time: %ld us\n", runtime);

    maximum = ksm_int_MAX(1, 2);
    printf("max: %d\n", maximum);
    printf("%.2f\n", arr2[SIZE-1]);

    ksm_TIMEIT(ksm_vector_f64_sqrt(arr1, arr2, SIZE), &runtime);
    printf("fast vector time: %lu us\n", runtime);

    free(arr1);
    free(arr2);
    return 0;
}
