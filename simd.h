#ifndef SIMD_H
#define SIMD_H

#include <stdio.h>

#ifdef __AVX512F__
#    define SIMD_ALIGN __attribute__ ((aligned (64)))
#else
#    ifdef __AVX__
#        define SIMD_ALIGN __attribute__ ((aligned (32)))
#    else
#        ifdef __SSE2__
#            define SIMD_ALIGN __attribute__ ((aligned (32)))
#        endif
#    endif
#endif

void ksm_add_double_array(
    double *result,
    const double *a,
    const double *b,
    size_t size
);

void ksm_div_double_array(
    double *result,
    const double *a,
    const double *b,
    size_t size
);

void ksm_sqrt_double_array(
    double *result,
    const double *a,
    size_t size
);

#endif /* SIMD_H */
