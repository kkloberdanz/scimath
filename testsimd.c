#include "simd.h"

int main() {
    double SIMD_ALIGN res[100];
    double SIMD_ALIGN a[100];
    int i;

    for (i = 0; i < 100; i++) {
        a[i] = (double)(i);
    }

    ksm_sqrt_double_array(res, a, 100);

    for (i = 0; i < 100; i++) {
        printf("sqrt(%f) = %f\n", a[i], res[i]);
    }
    puts("");
    return 0;
}
