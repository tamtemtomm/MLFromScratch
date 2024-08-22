#include <stdlib.h>
#include <string.h>
#include "linear_regression.h"

void fit(LinearRegression* model, double* X, double* y, int n_samples, int n_features) {
    double* y_pred = (double*)malloc(n_samples * sizeof(double));
    double* gradients_w = (double*)malloc(n_features * sizeof(double));
    double* diff = (double*)malloc(n_samples * sizeof(double));

    for (int iter = 0; iter < model->n_iters; iter++) {
        // Predict y using current weights and bias
        mat_vec_mult(X, model->weights, y_pred, n_samples, n_features);
        for (int i = 0; i < n_samples; i++) {
            y_pred[i] += model->bias;
        }

        // Compute gradients
        vec_subtract(y_pred, y, diff, n_samples);
        for (int j = 0; j < n_features; j++) {
            gradients_w[j] = (1.0 / n_samples) * dot_product(&X[j * n_samples], diff, n_samples);
        }
        double db = (1.0 / n_samples) * sum_vector(diff, n_samples);

        // Update parameters
        vec_update(model->weights, gradients_w, model->lr, n_features);
        model->bias -= model->lr * db;
    }

    free(y_pred);
    free(gradients_w);
    free(diff);
}
