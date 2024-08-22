#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_ops.h"

#define FEATURE_LEN 5

typedef struct LinearRegression {
    double lr;
    int n_iters;
    double weights[FEATURE_LEN];
    double bias[FEATURE_LEN];

    // Function pointer for the fit method
    void (*fit)(struct LinearRegression*, double*, double*, int, int);
} LinearRegression;

void fit(LinearRegression* model, double* X, double* y, int n_samples, int n_features) {
    double* y_pred = (double*)malloc(n_samples * sizeof(double));
    double* gradients_w = (double*)malloc(n_features * sizeof(double));
    double* diff = (double*)malloc(n_samples * sizeof(double));

    for (int iter = 0; iter < model->n_iters; iter++) {
        // Predict y using current weights and bias
        mat_vec_mult(X, model->weights, y_pred, n_samples, n_features);
        for (int i = 0; i < n_samples; i++) {
            y_pred[i] += model->bias[0]; // Assuming bias is a single value
        }

        // Compute gradients
        vec_subtract(y_pred, y, diff, n_samples);
        for (int j = 0; j < n_features; j++) {
            gradients_w[j] = (1.0 / n_samples) * dot_product(&X[j * n_samples], diff, n_samples);
        }
        double db = (1.0 / n_samples) * sum_vector(diff, n_samples);

        // Update parameters
        vec_update(model->weights, gradients_w, model->lr, n_features);
        model->bias[0] -= model->lr * db; // Assuming bias is a single value
    }

    free(y_pred);
    free(gradients_w);
    free(diff);
}

LinearRegression create_model() {
    LinearRegression model;
    model.lr = 0.01;
    model.n_iters = 100;

    // Seed the random number generator
    srand(time(NULL));

    // Initialize weights and bias with random values between 0 and 1
    for (int i = 0; i < FEATURE_LEN; i++) {
        model.weights[i] = (double)rand() / RAND_MAX;
        model.bias[i] = (double)rand() / RAND_MAX;
    }

    // Set the fit function pointer
    model.fit = fit;

    return model;
}

int main() {
    int n_samples = 10;
    int n_features = 3;

    // Allocate and initialize X, y, weights, and bias
    double* X = (double*)malloc(n_samples * n_features * sizeof(double));
    double* y = (double*)malloc(n_samples * sizeof(double));
    LinearRegression model = create_model();

    // Call the fit method
    model.fit(&model, X, y, n_samples, n_features);

    // Print results
    printf("Learning Rate: %f\n", model.lr);
    printf("Number of Iterations: %d\n", model.n_iters);
    printf("Weights:\n");
    for (int i = 0; i < n_features; i++) {
        printf(" %f", model.weights[i]);
    }
    printf("\nBias:\n %f\n", model.bias[0]); // Assuming bias is a single value

    free(X);
    free(y);

    return 0;
}
