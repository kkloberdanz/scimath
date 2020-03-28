#include <stdio.h>
#include <stdlib.h>

#include "simd.h"
#include "scimath.h"

#define SIZE 1000000001

int main() {
    float SIMD_ALIGN *res = aligned_alloc(SIMD_ALIGN_SIZE, SIZE * sizeof(float));
    float SIMD_ALIGN *a = aligned_alloc(SIMD_ALIGN_SIZE, SIZE * sizeof(float));
    int i;
    long runtime;

    for (i = 0; i < SIZE; i++) {
        a[i] = (float)(i);
    }

    ksm_TIMEIT(ksm_sqrt_float_array(res, a, SIZE), &runtime);

    printf("sqrt(%f) = %f\n", a[SIZE - 1], res[SIZE - 1]);
    printf("runtime: %ldms\n", runtime / 1000);
    return 0;
}
