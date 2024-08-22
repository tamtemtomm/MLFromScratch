#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "matrix_ops.h"

typedef struct LinearRegression {
    double lr;
    int n_iters;
    double weights[5];
    double bias;

    void (*fit)(struct LinearRegression*, double*, double*, int, int);
} LinearRegression;

void fit(LinearRegression* model, double* X, double* y, int n_samples, int n_features);

#endif // LINEAR_REGRESSION_H
