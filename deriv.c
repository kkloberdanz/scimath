#include <stdio.h>
#include <math.h>

#define H 0.0001

double first_deriv(double (*f)(double), double x) {
    return (f(x + H) - f(x - H)) / (2 * H);
}

double second_deriv(double (*f)(double), double x) {
    return (f(x + H) - 2 * f(x) + f(x - H)) / pow(H, 2);
}

double my_func(double x) {
    return pow(x, 3);
}

int main() {
    double x = 5.0;
    printf("f'(x) = %f\n", first_deriv(my_func, x));
    printf("f''(x) = %f\n", second_deriv(my_func, x));
}
