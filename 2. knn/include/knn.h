#ifndef KNN_H
#define KNN_H

#include "matrix.h"

typedef struct KNN
{
    int k;
    void (*fit)(struct KNN *, double **, double *, int, int);
    double *(*predict)(struct knn *, double **, int, int);
} KNN;

void fit(KNN *model, double **X, double *y, int n_samples, int n_features);
double *predict(KNN *model, double **X, int n_samples, int n_features);

KNN create_model(int k);

#endif