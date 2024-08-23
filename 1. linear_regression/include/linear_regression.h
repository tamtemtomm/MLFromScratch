// linaer_regression.h packages

#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "matrix.h"
#include "stdio.h"

typedef struct LinearRegression
{
    // Initialize the members
    FlexArray *weights;
    double bias;
    double lr;
    int n_iters;

    void (*fit)(struct LinearRegression *, double **, double *, int, int);
    double *(*predict)(struct LinearRegression *, double **, int, int);
} LinearRegression;

// Initialize fit method
void fit(LinearRegression *model, double **X, double *y, int n_samples, int n_features)
{
    // Allocate memory for mutable element in loop
    double *y_pred = (double *)malloc(n_samples * sizeof(double));
    double *dw = (double *)malloc(n_features * sizeof(double));
    double *loss = (double *)malloc(n_samples * sizeof(double));

    // Check if the memory allocated correctly
    if (y_pred == NULL || dw == NULL || loss == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Iterate trough n_iters
    for (int iter = 0; iter < model->n_iters; iter++) // Iterate based on model's n_iters
    {
        printf("Epoch %d\n", iter + 1);
        // Forward pass {dot(X, model.weights) + model.bias}
        vec_mult(X, model->weights->data, y_pred, n_samples, n_features);
        for (int i = 0; i < n_samples; i++)
        {
            y_pred[i] += model->bias;
        }

        // Count the loss {y_pred - y}
        vec_subtract(y_pred, y, loss, n_samples);

        // Get the gradient
        // dw = (1 / n_samples) * dot(X.T, loss)
        // db = (1 / n_samples) * sum(loss)
        for (int j = 0; j < n_features; j++)
        {
            // vec_at_column is get spesific column of an array
            dw[j] = (1.0 / n_samples) * vec_dot(vec_at_column(X, j, n_samples), loss, n_samples);
        }
        double db = (1.0 / n_samples) * vec_sum(loss, n_samples);

        // Update the weight
        // model.weights -= model.lr * dw
        // model.bias -= model.lr * db
        vec_update(model->weights->data, dw, model->lr, n_features);
        model->bias -= model->lr * db; // Assuming bias is a single value

        // Print output
        printf("y :\n");
        // for (int i = 0; i < n_samples; i++)
        // {
        //     printf("%f | ", y[i]);
        // }

        // printf("\ny_pred :\n");
        // for (int i = 0; i < n_samples; i++)
        // {
        //     printf("%f | ", y_pred[i]);
        // }

        printf("\nloss : %f\n", vec_sum(loss, n_samples)); // Print the loss
        printf("----------------------\n");
    }

    // Free the memory so it wont cause leakage
    free(y_pred);
    free(dw);
    free(loss);
}

double *predict(LinearRegression *model, double **X, int n_samples, int n_features)
{
    double *y_pred = (double *)malloc(n_samples * sizeof(double));

    vec_mult(X, model->weights->data, y_pred, n_samples, n_features);
    for (int i = 0; i < n_samples; i++)
    {
        y_pred[i] += model->bias; // Assuming bias is a single value
    }

    return y_pred;
}

// Initialize model constructor
LinearRegression create_model(double lr, int n_iters, int n_features)
{
    LinearRegression model;
    model.lr = lr;
    model.n_iters = n_iters;

    model.weights = (FlexArray *)malloc(sizeof(FlexArray) + n_features * sizeof(double));
    model.weights->size = n_features;
    for (int i = 0; i < model.weights->size; i++)
    {
        model.weights->data[i] = (double)rand() / RAND_MAX;
    }

    model.bias = 0;

    model.fit = fit;
    model.predict = predict;

    return model;
}

#endif // LINEAR_REGRESSION_H