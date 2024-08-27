#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdlib.h>

double sum(double *a, int length)
{
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += a[i];
    }

    return sum;
}

double euclidian_distance(double *a, double *b, int n_features)
{   
    double sum_squared_diff = 0;
    for (int i = 0; i < n_features; i++)
    {
        double diff = a[i] - b[i];
        sum_squared_diff += diff * diff;
    }

    double distance = sqrt(sum_squared_diff);
    return distance;
}

#endif
