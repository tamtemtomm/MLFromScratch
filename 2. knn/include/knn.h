#ifndef KNN_H
#define KNN_H

#include "matrix.h"
#include "argsort.h"
#include "counter.h"

typedef struct KNN
{
    int K;

    double **X_train;
    int *y_train;

    void (*fit)(struct KNN *, double **, int *, int, int);
    int *(*predict)(struct KNN *, double **, int, int, int);
    int (*_predict)(struct KNN *, double *, int, int, int);

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
}

int *predict(KNN *model, double **X, int n_train_samples, int n_test_samples, int n_features)
{
    int *results = (int *)malloc(n_test_samples * sizeof(int));
    for (int i = 0; i < n_test_samples; i++)
    {
        results[i] = model->_predict(model, X[i], n_train_samples, n_test_samples, n_features);
    }

    return results;
}

int _predict(KNN *model, double *X, int n_train_samples, int n_test_samples, int n_features)
{
    double *distances = (double *)malloc(n_train_samples * sizeof(double));
    int *sortedIndices = malloc(n_train_samples * sizeof(int));
    int *K_nearest_label = malloc(model->K * sizeof(int));

    // Get the distances
    for (int i = 0; i < n_train_samples; i++)
    {
        distances[i] = euclidian_distance(X, model->X_train[i], n_features);
    }

    // Sort distances and get indices
    argsort(distances, sortedIndices, n_train_samples);

    // Find K nearest labels (for demonstration)
    for (int i = 0; i < model->K; i++)
    {
        K_nearest_label[i] = model->y_train[sortedIndices[i]];
    }

    int most_common_label = find_most_common_label(K_nearest_label, model->K);

    // Free allocated memory
    free(distances);
    free(sortedIndices);
    free(K_nearest_label);

    return most_common_label; // You might want to return predictions here
}

KNN create_model(int K)
{
    KNN model;
    model.K = K;
    model.fit = fit;
    model.predict = predict;
    model._predict = _predict;

    printf("Model initialized!\n");

    return model;
}

#endif
