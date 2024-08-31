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

    // Create or get a dataset
    // Create the X
    double **X = (double **)malloc(N_SAMPLES * sizeof(double *));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        X[i] = (double *)malloc(N_FEATURES * sizeof(double));
        for (int j = 0; j < N_FEATURES; j++)
        {
            X[i][j] = (double)rand() / RAND_MAX;
        }
    }
    
    // Create the y
    int *y = (int *)malloc(N_SAMPLES * sizeof(int));
    for (int i = 0; i < N_SAMPLES; i++){
        y[i] = (int)rand() / RAND_MAX;
    }

    // Split datasets

    // Create a new model
    SVM model = create_model(LAMBDA, LEARNING_RATE, N_ITERS);

    // Fit the dataset into the model
    model.fit(&model, X, y, N_SAMPLES, N_FEATURES);

    // Predict using the trained model

    // Evaluate the results

    return 0;
}
