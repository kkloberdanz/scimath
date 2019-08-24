#ifndef SCIMATH_H
#define SCIMATH_H

#include <math.h>
#include <stdio.h>
#include <sys/time.h>

#ifndef ksm_DERIV_H_CONST
#define ksm_DERIV_H_CONST 0.0001
#endif

#ifndef ksm_VECTOR_START_CAPACITY
#define ksm_VECTOR_START_CAPACITY 4
#endif

#ifndef ksm_VECTOR_GROW_RATE
#define ksm_VECTOR_GROW_RATE 2
#endif

/******************************************************************************
 * By default use libc malloc, realloc, and free, can be overridden with custom
 * implementation if desired
 *****************************************************************************/
#ifndef ksm_MALLOC
#define ksm_MALLOC malloc
#endif

#ifndef ksm_FREE
#define ksm_FREE free
#endif

#ifndef ksm_REALLOC
#define ksm_REALLOC realloc
#endif

/******************************************************************************
 * Function prototypes
 *****************************************************************************/
double ksm_first_deriv(double (*f)(double), double x);
double ksm_second_deriv(double (*f)(double), double x);
void ksm_map(double (*f)(double), double *dst, const double *src, size_t size);
void ksm_vector_f64_sqrt(double *dst, const double *src, size_t size);

/******************************************************************************
 * Macros
 *****************************************************************************/
#define ksm_GENERIC_MAX( TYPE )           \
TYPE ksm_##TYPE##_MAX( TYPE a, TYPE b ) {   \
    return (a > b) ? a : b;           \
}

#define ksm_TIMEIT(stmt, time_buffer) \
    do { \
        struct timeval _ksm_start, _ksm_finish; \
        gettimeofday(&_ksm_start, NULL); \
        { \
            stmt; \
        } \
        gettimeofday(&_ksm_finish, NULL); \
        *time_buffer = \
            (1000000 * _ksm_finish.tv_sec + _ksm_finish.tv_usec) - \
            (1000000 * _ksm_start.tv_sec + _ksm_start.tv_usec); \
    } while (0)

/*#define ksm_GENERIC_VECTOR( TYPE ) \*/

struct ksm_Vector {
    size_t size;
    size_t capacity;
    int *data;
};

enum ksm_ErrorCode {
    ksm_NO_ERROR,
    ksm_OUT_OF_MEMORY
};

enum ksm_ErrorCode ksm_vector_init(struct ksm_Vector *v);
enum ksm_ErrorCode ksm_vector_push(struct ksm_Vector *v, int value);
enum ksm_ErrorCode ksm_vector_free(struct ksm_Vector *v);

#endif /* SCIMATH_H */
