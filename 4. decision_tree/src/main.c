#include <stdio.h>
#include <stdlib.h>

#include "decision_tree.h"

#define N_SAMPLES 10  // Use a small number of samples for debugging
#define N_FEATURES 2  // Use a small number of features for debugging
#define MAX_DEPTH 3
#define MIN_SAMPLES_SPLIT 2
#define TEST_SIZE 0.15
int main()
{
    // Fixed features
    double fixed_X[N_SAMPLES][N_FEATURES] = {
        {2.0, 3.0},
        {1.0, 1.0},
        {4.0, 5.0},
        {3.0, 3.0}
    };

    // Fixed labels
    int fixed_y[N_SAMPLES] = {1, 0, 1, 0};

    double **X = (double **)malloc(N_SAMPLES * sizeof(double *));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        X[i] = fixed_X[i];
    }

    int *y = fixed_y;

    // Initialize model
    DecisionTree model = create_model(MAX_DEPTH, MIN_SAMPLES_SPLIT);

    // Fit the model into the dataset
    model.fit(&model, X, y, N_SAMPLES, N_FEATURES);

    // Print the tree structure
    printf("Tree Structure:\n");
    print_tree(&model.tree, 0);

    // Predict using the model
    int *y_pred = model.predict(&model, X, N_SAMPLES, N_FEATURES);

    // Print predictions
    printf("Predictions:\n");
    for (int i = 0; i < N_SAMPLES; i++)
    {
        printf("Sample %d: Prediction: %d\n", i, y_pred[i]);
    }

    // Free allocated memory
    free(y_pred);

    return 0;
}