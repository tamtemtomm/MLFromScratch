#include <stdio.h>
#include <stdlib.h>
#include "linear_regression.h"

#define N_SAMPLES 100
#define N_FEATURES 10
#define LEARNING_RATE 0.1
#define N_ITERS 5000

int main()
{
    // Create a sample data with shape of [n_samples][N_FEATURES]
    double **X = (double **)malloc(N_SAMPLES * sizeof(double *));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        X[i] = (double *)malloc(N_FEATURES * sizeof(double));
    }

    for (int i = 0; i < N_SAMPLES; i++)
    {
        for (int j = 0; j < N_FEATURES; j++)
        {
            X[i][j] = (double)rand() / RAND_MAX;
        }
    }

    // Create a sample label
    double *y = (double *)malloc(N_SAMPLES * sizeof(double));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        y[i] = (double)rand() / RAND_MAX;
    }

    LinearRegression model = create_model(LEARNING_RATE, N_ITERS, N_FEATURES);
    model.fit(&model, X, y, N_SAMPLES, N_FEATURES);

    double *result = model.predict(&model, X, N_SAMPLES, N_FEATURES);
    printf("RESULT : \n");
    for (int i = 0; i < N_SAMPLES; i++)
    {
        printf("%f | ", result[i]);
    }

    // Free memory
    for (int i = 0; i < N_SAMPLES; i++) // Corrected: Free each row
    {
        free(X[i]);
    }

    free(model.weights);
    free(X);
    free(y);

    return 0;
}
