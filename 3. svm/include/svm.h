#ifndef SVM_H
#define SVM_H

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

typedef struct SVM
{
    double lambda;
    double lr;
    int n_iters;
    double *weights;
    double bias;

    void (*fit)(struct SVM *, double **, int *, int, int);
    double *(*predict)();
} SVM;

void fit(SVM *model, double **X, int *y, int n_samples, int n_features)
{
    // Initialize model weights based on the number of features (and bias too)
    model->weights = (double *)malloc(n_features * sizeof(double));
    for (int i = 0; i < n_features; i++)
    {
        model->weights[i] = (double)rand() / RAND_MAX;
        printf("Made%f\n",  model->weights[i]);
    }
    model->bias = (double)rand() / RAND_MAX;

    // Covert the label into 1 and -1
    double *y_ = (double *)malloc(n_samples * sizeof(double));
    for (int i = 0; i < n_samples; i++)
    {
        if (y[i] >= 0)
            y_[i] = 1;
        else
            y_[i] = -1;
    }

    // Fit the model n_iters times
    double *condition;
    for (int iter = 0; iter < model->n_iters; iter++)
    {
        for (int i = 0; i < n_features; i++)
        {
            printf("%f\n", model->weights[i]);
        }

        for (int index = 0; index < n_samples; index++)
        {
            double condition = y_[index] * (vec_dot(X[index], model->weights, n_features) - model->bias);
            if (condition >= 1)
            {
                for (int i = 0; i < n_features; i++)
                {
                    model->weights[i] -= model->lr * (2 * model->lambda * model->weights[i]);
                }
            }
            else
            {
                for (int i = 0; i < n_features; i++)
                {
                    model->weights[i] -= model->lr * ((2 * model->lambda * model->weights[i]) - vec_dot_scalar(X[index], y_[index], n_features));
                    model->bias -= model->lr * y_[index];
                }
            }
        }
    }

    printf("Completed\n");
};
double *predict();

SVM create_model(double lambda, double lr, int n_iters)
{
    SVM model;
    model.lambda = lambda;
    model.lr = lr;
    model.n_iters = n_iters;

    model.fit = fit;
    // model.predict = predict;

    printf("Model initialized!\n");

    return model;
}

#endif