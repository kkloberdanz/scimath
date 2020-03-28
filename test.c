/******************************************************************************
 * Copyright 2019 Kyle Kloberdanz
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "scimath.h"
#include "template.h"
#include "simd.h"

/*#define SIZE 100000000*/

ksm_GENERIC_MAX(int)

double times_2(double x) {
    return x * 2;
}

double my_func(double x) {
    return pow(x, 3);
}

void test_vector() {
    size_t i;
    char c;
    struct ksm_size_t_Vector v;
    struct ksm_double_Vector v2;
    ksm_string str;
    ksm_size_t_vector_init(&v);

    for (i = 0; i < 100; i++) {
        ksm_size_t_vector_push(&v, i);
    }

    for (i = 0; i < v.size; i++) {
        printf("%zu, ", v.data[i]);
    }
    puts("");
    ksm_size_t_vector_free(&v);

    ksm_double_vector_init(&v2);
    for (i = 0; i < 100; i++) {
        ksm_double_vector_push(&v2, sqrt(i));
    }

    for (i = 0; i < v2.size; i++) {
        printf("%f, ", v2.data[i]);
    }
    puts("");

    for (i = v2.size - 1; i > 0; i--) {
        fprintf(stderr, "%f, ", v2.data[i]);
        ksm_double_vector_pop(&v2);
    }
    puts("");

    ksm_double_vector_free(&v2);

    ksm_char_vector_init(&str);

    for (c = 'a'; c <= 'z'; c++) {
        ksm_char_vector_push(&str, c);
    }
    ksm_char_vector_push(&str, '\0');
    puts(str.data);
    ksm_char_vector_free(&str);
}

void test_arena_allocator() {
    struct Arena arena;
    size_t i;
    size_t total = 0;
    srand(10);
    kk_arena_init(&arena);
    for (i = 0; i < 100000; i++) {
        size_t bytes = rand() % 1024;
        void *ptr = kk_arena_alloc(bytes, &arena);
        /*void *ptr = malloc(bytes);*/

        /*fprintf(stderr, "allocating %zu bytes\n", bytes);*/
        total += (size_t)ptr;
        /*fprintf(stderr, "ptr = %p, i = %zu\n", ptr, i);*/
    }
    fprintf(stderr, "dummy: %zu\n", total);
    kk_arena_free_all(&arena);
}

void test_track_malloc() {
    int i;
    size_t total = 0;
    MemoryVec memory;
    memory_vec_init(&memory);
    srand(10);
    for (i = 0; i < 100000; i++) {
        size_t bytes = rand() % 1024;
        void *ptr = kk_track_malloc(bytes, &memory);

        /*fprintf(stderr, "allocating %zu bytes\n", bytes);*/
        total += (size_t)ptr;
        /*fprintf(stderr, "ptr = %p, i = %zu\n", ptr, i);*/
    }
    fprintf(stderr, "dummy: %zu\n", total);
    kk_track_free(&memory);
}

int main() {
    /*
    double x = 5.0;
    double *arr1 = malloc(sizeof(double) * SIZE);
    double *arr2 = malloc(sizeof(double) * SIZE);
    size_t i;
    int maximum;
    long runtime;

    printf("f'(x) = %f\n", ksm_first_deriv(my_func, x));
    printf("f''(x) = %f\n", ksm_second_deriv(my_func, x));
    
    for (i = 0; i < SIZE; i++) {
        arr1[i] = i;
    }

    ksm_TIMEIT(ksm_map(sqrt, arr2, arr1, SIZE), &runtime);
    printf("ksm_map time: %ld us\n", runtime);

    maximum = ksm_int_MAX(1, 2);
    printf("max: %d\n", maximum);
    printf("%.2f\n", arr2[SIZE-1]);

    ksm_TIMEIT(ksm_vector_f64_sqrt(arr1, arr2, SIZE), &runtime);
    printf("fast vector time: %lu us\n", runtime);

    free(arr1);
    free(arr2);

    test_vector();
    test_arena_allocator();
    test_track_malloc();
    */
}
