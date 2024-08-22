#include <stdio.h>
#include <stdlib.h>
#include "linear_regression.h"

#define N_SAMPLES 10
#define N_FEATURES 5
#define LEARNING_RATE 0.01
#define N_ITERS 100

LinearRegression create_model(double lr, int n_iters)
{
    LinearRegression model;
    model.lr = lr;
    model.n_iters = n_iters;
    model.bias = (double)rand() / RAND_MAX;

    for (int i = 0; i < N_FEATURES; i++)
    {
        model.weights[i] = (double)rand() / RAND_MAX;
    }

    model.fit = fit;

    return model;
}

int main()
{
    int n_features = N_FEATURES;
    int n_samples = N_SAMPLES;

    // Create a sample data with shape of [n_samples][n_features]
    double **X = (double **)malloc(n_samples * sizeof(double *));
    for (int i = 0; i < n_samples; i++)
    {
        X[i] = (double *)malloc(n_features * sizeof(double));
    }

    for (int i = 0; i < N_SAMPLES; i++)
    {
        for (int j = 0; j < N_FEATURES; j++)
        {
            X[i][j] = (double)rand() / RAND_MAX;
        }
    }

    // Create a sample label
    double *y = (double *)malloc(n_samples * sizeof(double));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        y[i] = (double)rand() / RAND_MAX;
    }

    LinearRegression model = create_model(LEARNING_RATE, N_ITERS);
    model.fit(&model, X, y, n_samples, n_features);

    // Free memory
    for (int i = 0; i < n_samples; i++) // Corrected: Free each row
    {
        free(X[i]);
    }
    free(X);
    free(y);

    return 0;
}
