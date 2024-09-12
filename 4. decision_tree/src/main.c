#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "decision_tree.h"

#define N_SAMPLES 10 // Use a small number of samples for debugging
#define N_FEATURES 2 // Use a small number of features for debugging
#define MAX_DEPTH 3
#define MIN_SAMPLES_SPLIT 2
#define TEST_SIZE 0.15

int main()
{

    srand(time(NULL));
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
    if (y == NULL)
    {
        // Check if malloc succeeded
        printf("Memory allocation failed\n");
        return 1;
    }

    // Generate random binary labels (0 or 1)
    for (int i = 0; i < N_SAMPLES; i++)
    {
        y[i] = rand() % 2;    // Generate 0 or 1
        printf("%d\n", y[i]); // Print each generated value
    }

    // Free allocated memory for y
    free(y);

    // Initialize model
    // DecisionTree model = create_model(MAX_DEPTH, MIN_SAMPLES_SPLIT);

    // // Fit the model into the dataset
    // model.fit(&model, X, y, N_SAMPLES, N_FEATURES);

    // // Print the tree structure
    // printf("Tree Structure:\n");
    // print_tree(&model.tree, 0);

    // // Predict using the model
    // int *y_pred = model.predict(&model, X, N_SAMPLES, N_FEATURES);

    // // Print predictions
    // printf("Predictions:\n");
    // for (int i = 0; i < N_SAMPLES; i++)
    // {
    //     printf("Sample %d: Prediction: %d\n", i, y_pred[i]);
    // }

    // // Free allocated memory
    // free(y_pred);

    return 0;
}