#include <stdio.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <math.h>

#include "simd.h"

void ksm_sqrt_double_array(
    double *result,
    const double *a,
    size_t size
) {
    size_t i = 0;

    /* 
     * Note we are doing as many blocks of 8 as we can.
     * If the size is not divisible by 8 then we will have some left over
     * that will then be performed serially.
     */

#ifdef __AVX512F__
    /* AVX-512 */
    for(; i < (size & ~0x7); i += 8) {
        const __m512d kA8 = _mm512_load_pd(&a[i]);
        const __m512d kRes = _mm512_sqrt_pd(kA8);
        _mm512_stream_pd(&result[i], kRes);
    }
#endif

#ifdef __AVX__
    /* AVX loop */
    for (; i < (size & ~0x3); i += 4) {
        const __m256d kA4 = _mm256_load_pd(&a[i]);
        const __m256d kRes = _mm256_sqrt_pd(kA4);
        _mm256_stream_pd(&result[i], kRes);
    }
#endif

#ifdef __SSE2__
    /* SSE2 loop */
    for (; i < (size & ~0x1); i += 2) {
        const __m128d kA2 = _mm_load_pd(&a[i]);
        const __m128d kRes = _mm_sqrt_pd(kA2);
        _mm_stream_pd(&result[i], kRes);
    }
#endif

    /* Serial loop */
    for(; i < size; i++) {
        result[i] = sqrt(a[i]);
    }
}

void ksm_div_double_array(
    double *result,
    const double *a,
    const double *b,
    size_t size
) {
    size_t i = 0;

    /* 
     * Note we are doing as many blocks of 8 as we can.
     * If the size is not divisible by 8 then we will have some left over
     * that will then be performed serially.
     */

#ifdef __AVX512F__
    /* AVX-512 */
    for(; i < (size & ~0x7); i += 8) {
        const __m512d kA8 = _mm512_load_pd(&a[i]);
        const __m512d kB8 = _mm512_load_pd(&b[i]);
        const __m512d kRes = _mm512_div_pd(kA8, kB8);
        _mm512_stream_pd(&result[i], kRes);
    }
#endif

#ifdef __AVX__
    /* AVX loop */
    for (; i < (size & ~0x3); i += 4) {
        const __m256d kA4 = _mm256_load_pd(&a[i]);
        const __m256d kB4 = _mm256_load_pd(&b[i]);
        const __m256d kRes = _mm256_div_pd(kA4, kB4);
        _mm256_stream_pd(&result[i], kRes);
    }
#endif

#ifdef __SSE2__
    /* SSE2 loop */
    for (; i < (size & ~0x1); i += 2) {
        const __m128d kA2 = _mm_load_pd(&a[i]);
        const __m128d kB2 = _mm_load_pd(&b[i]);
        const __m128d kRes = _mm_div_pd(kA2, kB2);
        _mm_stream_pd(&result[i], kRes);
    }
#endif

    /* Serial loop */
    for(; i < size; i++) {
        result[i] = a[i] + b[i];
    }
} 

void ksm_add_double_array(
    double *result,
    const double *a,
    const double *b,
    size_t size
) {
    size_t i = 0;

    /* 
     * Note we are doing as many blocks of 8 as we can.
     * If the size is not divisible by 8 then we will have some left over
     * that will then be performed serially.
     */

#ifdef __AVX512F__
    /* AVX-512 */
    for(; i < (size & ~0x7); i += 8) {
        const __m512d kA8 = _mm512_load_pd(&a[i]);
        const __m512d kB8 = _mm512_load_pd(&b[i]);
        const __m512d kRes = _mm512_add_pd(kA8, kB8);
        _mm512_stream_pd(&result[i], kRes);
    }
#endif

#ifdef __AVX__
    /* AVX loop */
    for (; i < (size & ~0x3); i += 4) {
        const __m256d kA4 = _mm256_load_pd(&a[i]);
        const __m256d kB4 = _mm256_load_pd(&b[i]);
        const __m256d kRes = _mm256_add_pd(kA4, kB4);
        _mm256_stream_pd(&result[i], kRes);
    }
#endif

#ifdef __SSE2__
    /* SSE2 loop */
    for (; i < (size & ~0x1); i += 2) {
        const __m128d kA2 = _mm_load_pd(&a[i]);
        const __m128d kB2 = _mm_load_pd(&b[i]);
        const __m128d kRes = _mm_add_pd(kA2, kB2);
        _mm_stream_pd(&result[i], kRes);
    }
#endif

    /* Serial loop */
    for(; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

#ifdef SIMD_TEST
int main() {
    double SIMD_ALIGN res[100];
    double SIMD_ALIGN a[100];
    double SIMD_ALIGN b[100];
    int i;

    for (i = 0; i < 100; i++) {
        a[i] = (double)(i & 0xf);
        b[i] = (double)(i | 0xa);
    }
    ksm_add_double_array(res, a, b, 100);
    for (i = 0; i < 100; i++) {
        printf("%f ", res[i]);
    }
    puts("");
}
#endif /* SIMD_TEST */
