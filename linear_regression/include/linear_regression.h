#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "matrix.h"
typedef struct LinearRegression
{
    double weights[5];
    double bias;
    double lr;
    int n_iters;

    void (*fit)(struct LinearRegression *, double **, double *, int, int);
} LinearRegression;

void fit(LinearRegression *model, double **X, double *y, int n_samples, int n_features)
{
    double *y_pred = (double *)malloc(n_samples * sizeof(double));
    double *gradients_w = (double *)malloc(n_features * sizeof(double));
    double *diff = (double *)malloc(n_samples * sizeof(double));

    if (y_pred == NULL || gradients_w == NULL || diff == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int iter = 0; iter < model->n_iters; iter++) // Iterate based on model's n_iters
    {
        printf("Weights : %f\n", model->weights[0]);
        vec_mult(X, model->weights, y_pred, n_samples, n_features);

        for (int i = 0; i < n_samples; i++)
        {
            y_pred[i] += model->bias; // Assuming bias is a single value
        }

        vec_subtract(y_pred, y, diff, n_samples);

        for (int j = 0; j < n_features; j++)
        {
            gradients_w[j] = (1.0 / n_samples) * vec_dot(vec_at_column(X, j, n_samples), diff, n_samples);
            // printf("Gradient : %f\n", gradients_w[j]);
        }

        double db = (1.0 / n_samples) * vec_sum(diff, n_samples);
        // printf("db : %f\n", db);

        vec_update(model->weights, gradients_w, model->lr, n_features);

        printf("diff : %f\n", diff[0]);
        model->bias -= model->lr * db; // Assuming bias is a single value
    }

    free(y_pred);
    free(gradients_w);
    free(diff);
}
#endif // LINEAR_REGRESSION_H