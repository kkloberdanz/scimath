#include "simd.h"

#define SIZE 1001

int main() {
    float SIMD_ALIGN res[SIZE];
    float SIMD_ALIGN a[SIZE];
    int i;

    for (i = 0; i < SIZE; i++) {
        a[i] = (float)(i);
    }

    ksm_sqrt_float_array(res, a, SIZE);

    for (i = 0; i < SIZE; i++) {
        printf("sqrt(%f) = %f\n", a[i], res[i]);
    }
    puts("");
    return 0;
}
