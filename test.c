#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "scimath.h"
#include "template.h"

#define SIZE 100000000

ksm_GENERIC_MAX(int)

double times_2(double x) {
    return x * 2;
}

double my_func(double x) {
    return pow(x, 3);
}

void test_vector() {
    int i;
    struct ksm_int_Vector v;
    struct ksm_double_Vector v2;
    ksm_int_vector_init(&v);

    for (i = 0; i < 100; i++) {
        ksm_int_vector_push(&v, i);
    }

    for (i = 0; i < 100; i++) {
        printf("%d, ", v.data[i]);
    }
    puts("");
    ksm_int_vector_free(&v);

    ksm_double_vector_init(&v2);
    for (i = 0; i < 100; i++) {
        ksm_double_vector_push(&v2, sqrt(i));
    }

    for (i = 0; i < 100; i++) {
        printf("%f, ", v2.data[i]);
    }
    puts("");
    ksm_double_vector_free(&v2);
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

    test_vector();
    return 0;
}
