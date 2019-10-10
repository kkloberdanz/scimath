/******************************************************************************
 * Copyright 2019 Kyle Kloberdanz
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "scimath.h"

#define MAX(A, B) ((A) > (B)) ? (A) : (B)
#define PAGE_SIZE 4096

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

static struct MemoryPoolNode *kk_do_malloc(size_t size) {
    size_t capacity = MAX(size, PAGE_SIZE);
    void *memory = malloc(capacity);
    struct MemoryPoolNode *pool = malloc(sizeof(struct MemoryPoolNode));
    pool->memory = memory;
    pool->next = NULL;
    pool->index = size + 1;
    pool->capacity = capacity;
    return pool;
}

void kk_arena_init(struct Arena *arena) {
    arena->_pool = NULL;
}

void *kk_arena_alloc(size_t size, struct Arena *arena) {
    if (arena->_pool == NULL) {
        /* first allocation */
        struct MemoryPoolNode *pool = kk_do_malloc(size);
        arena->_pool = pool;
        return pool->memory;
    } else {
        struct MemoryPoolNode *pool;
        struct MemoryPoolNode *prev = NULL;
        size_t i = 0;
        for (pool = arena->_pool; pool != NULL; pool = pool->next) {
            size_t bytes_left = pool->capacity - pool->index;
            if (size <= bytes_left) {
                /* has available memory in existing pool */
                size_t index = pool->index;
                pool->index += size;
                return pool->memory + index;
            }
            i++;
            if (pool) {
                prev = pool;
            }
        }
        /* needs to add new pool */
        pool = kk_do_malloc(size);
        prev->next = pool;
        return pool->memory;
    }
}

void kk_arena_free_all(struct Arena *arena) {
    struct MemoryPoolNode *pool;
    struct MemoryPoolNode *head;
    pool = arena->_pool;

    /*for (pool = arena->_pool; pool != NULL; pool = pool->next) {*/
    while (pool) {
        head = pool->next;
        free(pool->memory);
        free(pool);
        pool = head;
    }
}
