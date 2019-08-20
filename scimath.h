#ifndef SCIMATH_H
#define SCIMATH_H

#include <math.h>
#include <stdio.h>
#include <sys/time.h>

#ifndef DERIV_H_CONST
#define DERIV_H_CONST 0.0001
#endif

/*
 * Functions
 */

double ksm_first_deriv(double (*f)(double), double x);
double ksm_second_deriv(double (*f)(double), double x);
void ksm_map(double (*f)(double), double *dst, const double *src, size_t size);
void ksm_vector_f64_sqrt(double *dst, const double *src, size_t size);

/*
 * Macros
 */
#define ksm_GENERIC_MAX( TYPE )           \
TYPE ksm_##TYPE##_MAX( TYPE a, TYPE b ) {   \
    return (a > b) ? a : b;           \
}

#define ksm_TIMEIT(stmt, time_buffer) \
    do { \
        struct timeval _ksm_start, _ksm_finish; \
        gettimeofday(&_ksm_start, NULL); \
        (stmt); \
        gettimeofday(&_ksm_finish, NULL); \
        *time_buffer = \
            (1000000 * _ksm_finish.tv_sec + _ksm_finish.tv_usec) - \
            (1000000 * _ksm_start.tv_sec + _ksm_start.tv_usec); \
    } while(0)

#endif /* SCIMATH_H */
