#include <stdio.h>
#include <stdlib.h>

#include "decision_tree.h"

#define N_SAMPLES 100
#define N_FEATURES 5
#define MAX_DEPTH 10
#define MIN_SAMPLES_SPLIT 2
#define TEST_SIZE 0.15

int main()
{
    // Make a sample features
    double **X = (double **)malloc(N_SAMPLES * sizeof(double *));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        X[i] = (double *)malloc(N_FEATURES * sizeof(double));
        for (int j = 0; j < N_FEATURES; j++)
        {
            X[i][j] = (double)rand() / RAND_MAX;
            // printf("DEBUG------------\n");
            // printf("%d\n", X[i][j]);
        }
    }

    // Make a sample labels
    int *y = (int *)malloc(N_SAMPLES * sizeof(int));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        y[i] = (rand() % 3); // Generates 1 or 0

        // printf("DEBUG------------\n");
        // printf("%d\n", y[i]);
    }

    // Split datasets

    // Initializes model
    DecisionTree model = create_model(MAX_DEPTH, MIN_SAMPLES_SPLIT);
    model._best_split(&model, X, y, N_SAMPLES, N_FEATURES);

    // Fit the model into the dataset
    // model.fit(@model, X_train, y_train, N_SAMPLES, N_FEATURES);

    // Predict using models
    // int* y_pred = model.predict(@model, X_test, N_SAMPLES, N_FEATURES);

    // Get the accuracy of the model
    return 0;
}