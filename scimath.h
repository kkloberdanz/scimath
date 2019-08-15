#ifndef SCIMATH_H
#define SCIMATH_H

#include <math.h>
#include <stdio.h>

#ifndef DERIV_H_CONST
#define DERIV_H_CONST 0.0001
#endif

double first_deriv(double (*f)(double), double x);
double second_deriv(double (*f)(double), double x);
double my_func(double x);
void ksm_map(double (*f)(double), double *src, double *dst, size_t size);

#endif /* SCIMATH_H */
