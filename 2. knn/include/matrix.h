#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

double sum(double *a, int length)
{
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += a[i];
    }

    return sum;
}

double euclidian_distance(double **a, double *b, int n_samples, int n_features)
{
    double *diff = (double *)malloc(n_samples * sizeof(double));
    for (int i = 0; i < n_samples; i++)
    {
        for (int j = 0; j < n_features; j++)
        {
            diff[i] = pow(a[i][j] - b[j], 2);
        }
    }

    double summed_diff = sum(diff, n_samples);
    double distance = sqrt(summed_diff);
    return distance;
}

double *get_distances(double **a, double **b, int n_train_samples, int n_test_samples, int n_features)
{
    double *distances = (double *)malloc(n_train_samples * sizeof(double));
    for (int i = 0; i < n_train_samples; i++)
    {
        distances[i] = euclidian_distance(a, b[i], n_test_samples, n_features);
    }

    return distances;
}

#endif