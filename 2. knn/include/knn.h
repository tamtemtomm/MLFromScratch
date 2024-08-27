#ifndef KNN_H
#define KNN_H

#include "matrix.h"

typedef struct KNN
{
    int K;

    double **X_train;
    int *y_train;

    void (*fit)(struct KNN *, double **, int *, int, int);
    double *(*predict)(struct KNN *, double **, int, int);
} KNN;

void fit(KNN *model, double **X, int *y, int n_samples, int n_features)
{

    // Initialize model features sizes
    model->X_train = (double **)malloc(n_samples * sizeof(double *));
    model->y_train = (int *)malloc(n_samples * (sizeof(int)));

    for (int i = 0; i < n_samples; i++)
    {
        // Input X_train features
        model->X_train[i] = (double *)malloc(n_features * sizeof(double));
        for (int j = 0; j < n_features; j++)
        {
            model->X_train[i][j] = X[i][j];
        }

        // Input y_train features
        model->y_train[i] = y[i];
    }
};
double *predict(KNN *model, double **X, int n_samples, int n_features) {

};

KNN create_model(int K)
{
    KNN model;
    model.K = K;
    model.fit = fit;
    model.predict = predict;

    printf("Model initialized!\n");

    return model;
};

#endif