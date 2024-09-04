#include <stdio.h>
#include <stdlib.h>
#include "svm.h"

#define LAMBDA 0.01
#define LEARNING_RATE 0.01
#define N_ITERS 100

#define N_SAMPLES 10
#define N_FEATURES 2

int main()
{
    // Create dataset
    double **X = (double **)malloc(N_SAMPLES * sizeof(double *));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        X[i] = (double *)malloc(N_FEATURES * sizeof(double));
        for (int j = 0; j < N_FEATURES; j++)
        {
            X[i][j] = (double)rand() / RAND_MAX;
        }
    }

    int *y = (int *)malloc(N_SAMPLES * sizeof(int));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        y[i] = (rand() % 2) * 2 - 1; // Generates -1 or 1
    }

    // Create and train model
    SVM model = create_model(LAMBDA, LEARNING_RATE, N_ITERS);
    model.fit(&model, X, y, N_SAMPLES, N_FEATURES);

    // Predict
    int *results = model.predict(&model, X, N_SAMPLES, N_FEATURES);
    for (int i = 0; i < N_SAMPLES; i++)
    {
        printf("%d ", results[i]);
    }
    printf("\n");

    // Free allocated memory
    for (int i = 0; i < N_SAMPLES; i++)
    {
        free(X[i]);
    }
    free(X);
    free(y);
    free(results);

    return 0;
}
