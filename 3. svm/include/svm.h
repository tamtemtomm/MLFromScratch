#ifndef SVM_H
#define SVM_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct SVM {
    double lambda;
    double lr;
    int n_iters;
    double *weights;
    double bias;

    void (*fit)(struct SVM *, double **, int *, int, int);
    int *(*predict)(struct SVM *, double **, int, int);
} SVM;

void fit(SVM *model, double **X, int *y, int n_samples, int n_features) {
    model->weights = (double *)malloc(n_features * sizeof(double));
    for (int i = 0; i < n_features; i++) {
        model->weights[i] = 0; // Initialize weights to 0
    }
    model->bias = 0;

    double *y_ = (double *)malloc(n_samples * sizeof(double));
    for (int i = 0; i < n_samples; i++) {
        y_[i] = y[i] >= 0 ? 1 : -1;
    }

    for (int iter = 0; iter < model->n_iters; iter++) {
        for (int index = 0; index < n_samples; index++) {
            double condition = y_[index] * (vec_dot(X[index], model->weights, n_features) - model->bias);
            if (condition >= 1) {
                for (int i = 0; i < n_features; i++) {
                    model->weights[i] -= model->lr * (2 * model->lambda * model->weights[i]);
                }
            } else {
                for (int i = 0; i < n_features; i++) {
                    model->weights[i] -= model->lr * (2 * model->lambda * model->weights[i] - y_[index] * X[index][i]);
                }
                model->bias -= model->lr * y_[index];
            }
        }
    }
    free(y_);
}

int *predict(SVM *model, double **X, int n_samples, int n_features) {
    int *result = (int *)malloc(n_samples * sizeof(int));
    for (int i = 0; i < n_samples; i++) {
        double condition = vec_dot(X[i], model->weights, n_features) - model->bias;
        result[i] = condition >= 0 ? 1 : -1;
    }
    return result;
}

SVM create_model(double lambda, double lr, int n_iters) {
    SVM model;
    model.lambda = lambda;
    model.lr = lr;
    model.n_iters = n_iters;

    model.fit = fit;
    model.predict = predict;

    return model;
}

#endif
