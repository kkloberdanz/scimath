#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "scimath.h"

double ksm_first_deriv(double (*f)(double), double x) {
    return (f(x + ksm_DERIV_H_CONST) - f(x - ksm_DERIV_H_CONST)) /
           (2 * ksm_DERIV_H_CONST);
}

double ksm_second_deriv(double (*f)(double), double x) {
    return (f(x + ksm_DERIV_H_CONST) - 2 * f(x) + f(x - ksm_DERIV_H_CONST)) /
           (ksm_DERIV_H_CONST * ksm_DERIV_H_CONST);
}

void ksm_map(
    double (*f)(double),
    double *dst,
    const double *src,
    size_t size
) {
    size_t i;
    #pragma omp parallel for
    for (i = 0; i < size; i++) {
        dst[i] = f(src[i]);
    }
}

/*
 * TODO: optimize with SIMD and intrinsic sqrt
 */
void ksm_vector_f64_sqrt(double *dst, const double *src, size_t size) {
    size_t i;
    #pragma omp parallel for
    for (i = 0; i < size; i++) {
        dst[i] = sqrt(src[i]);
    }
}
