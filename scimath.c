#include <stdio.h>
#include <math.h>
#include <omp.h>

#include "scimath.h"

double first_deriv(double (*f)(double), double x) {
    return (f(x + DERIV_H_CONST) - f(x - DERIV_H_CONST)) / \
           (2 * DERIV_H_CONST);
}

double second_deriv(double (*f)(double), double x) {
    return (f(x + DERIV_H_CONST) - 2 * f(x) + f(x - DERIV_H_CONST)) / \
           (DERIV_H_CONST * DERIV_H_CONST);
}

double my_func(double x) {
    return pow(x, 3);
}

void ksm_map(double (*f)(double), double *src, double *dst, size_t size) {
    size_t i;
    #pragma omp parallel for
    for (i = 0; i < size; i++) {
        dst[i] = f(src[i]);
    }
}
