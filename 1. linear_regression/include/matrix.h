#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef struct
{
    int size;
    double data[]; // Flexible array member
} FlexArray;

// function for multiplication of data (n_samples, n_features) @ weights (n_features)
void vec_mult(double **data, const double *weight, double *result, int n_samples, int n_features)
{   
    for (int i = 0; i < n_samples; i++)
    {
        result[i] = 0;
        for (int j = 0; j < n_features; j++)
        {
            // printf("----------------------------\n");
            // printf("Data  : %f\n", data[i][j]);
            // printf("Weight:%f\n", weight[j]);
            result[i] += data[i][j] * weight[j];
        }
        // printf("Result:%f\n", result[i]);
    }
}

double vec_dot(double *vec1, const double *vec2, int length)
{
    double result = 0;
    for (int i = 0; i < length; i++)
    {
        result += vec1[i] * vec2[i];
    }

    return result;
}

double vec_sum(const double *vec, int length)
{
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += vec[i];
    }
    return sum;
}

void vec_subtract(const double *vec1, const double *vec2, double *result, int length)
{
    for (int i = 0; i < length; i++)
    {
        // printf("vec1: %f\n", vec1[i]);
        // printf("vec2: %f\n", vec2[i]);

        result[i] = vec1[i] - vec2[i];
        // printf("result: %f\n", result[i]);
        // printf("--------------------------------\n");
    }
}

void vec_update(double *vec, double *w, double lr, int length)
{
    for (int i = 0; i < length; i++)
    {
        vec[i] -= lr * w[i];
    }
}

double *vec_at_column(double **X, int column_index, int n_samples)
{
    double *column = (double *)malloc(n_samples * sizeof(double));
    for (int i = 0; i < n_samples; i++)
    {
        column[i] = X[i][column_index];
    }

    return column;
}
#endif // MATRIX_H