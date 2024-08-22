#include <stdio.h>
#include <stdlib.h>
#include "linear_regression.h"

#define FEATURE_LEN 5

LinearRegression create_model() {
    LinearRegression model;
    model.lr = 0.01;
    model.n_iters = 100;
    model.bias = 0;

    // Initialize weights with random values between 0 and 1
    for (int i = 0; i < FEATURE_LEN; i++) {
        model.weights[i] = (double)rand() / RAND_MAX;
    }

    // Set the fit function pointer
    model.fit = fit;

    return model;
}

int main() {
    int n_samples = 10;
    int n_features = 3;

    // Allocate and initialize X and y
    double* X = (double*)malloc(n_samples * n_features * sizeof(double));
    double* y = (double*)malloc(n_samples * sizeof(double));

    // Initialize X and y with some values here

    LinearRegression model = create_model();
    model.fit(&model, X, y, n_samples, n_features);

    // Print results
    printf("Learning Rate: %f\n", model.lr);
    printf("Number of Iterations: %d\n", model.n_iters);
    printf("Weights:\n");
    for (int i = 0; i < n_features; i++) {
        printf(" %f", model.weights[i]);
    }
    printf("\nBias: %f\n", model.bias);

    free(X);
    free(y);

    return 0;
}
