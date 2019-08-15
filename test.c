#include <stdio.h>
#include <stdlib.h>

#include "scimath.h"

#define SIZE 100000000

GENERIC_MAX(int)

double times_2(double x) {
    return x * 2;
}

double my_func(double x) {
    return pow(x, 3);
}

volatile double *array;

int main() {
    double x = 5.0;
    double *arr1 = malloc(sizeof(double) * SIZE);
    double *arr2 = malloc(sizeof(double) * SIZE);
    size_t i;
    int maximum;

    printf("f'(x) = %f\n", first_deriv(my_func, x));
    printf("f''(x) = %f\n", second_deriv(my_func, x));
    
    for (i = 0; i < SIZE; i++) {
        arr1[i] = i;
    }

    ksm_map(sqrt, arr1, arr2, SIZE);
    array = arr2;

    maximum = int_MAX(1, 2);
    printf("%d\n", maximum);
    printf("%.2f\n", array[SIZE-1]);

    free(arr1);
    free(arr2);
    return 0;
}
