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

enum ksm_ErrorCode ksm_vector_init(struct ksm_Vector *v) {
    int *data = ksm_MALLOC(sizeof(int) * ksm_VECTOR_START_CAPACITY);
    v->size = 0;
    v->capacity = ksm_VECTOR_START_CAPACITY;
    v->data = data;
    if (data == NULL) {
        return ksm_OUT_OF_MEMORY;
    } else {
        return ksm_NO_ERROR;
    }
}

enum ksm_ErrorCode ksm_vector_push(struct ksm_Vector *v, int value) {
    if (v->size < v->capacity) {
        v->data[v->size] = value;
        v->size++;
        return ksm_NO_ERROR;
    } else {
        const size_t new_capacity = ksm_VECTOR_GROW_RATE * v->capacity;
        printf("resizing from %ld to %ld\n", v->capacity, new_capacity);
        v->capacity = new_capacity;
        v->data = realloc(v->data, v->capacity * sizeof(int));
        if (v->data != NULL) {
            v->data[v->size] = value;
            v->size++;
            return ksm_NO_ERROR;
        } else {
            return ksm_OUT_OF_MEMORY;
        }
    }
}

enum ksm_ErrorCode ksm_vector_free(struct ksm_Vector *v) {
    ksm_FREE(v->data);
    return ksm_NO_ERROR;
}
