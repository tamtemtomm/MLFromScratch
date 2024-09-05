#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <math.h>

// Get the index of maximum value in the matrix
int vec_argmax(int *a, int len)
{
    int max = 0;
    int id = 0;

    for (int i = 0; i < len; i++)
    {
        if (max < a[i])
        {
            max = a[i];
            id = i;
        }
    }

    return id;
}

// Function to check if the element is in matrix
int is_in_vec(int *a, int el, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] == el)
        {
            return 1; // eLement found
        }
    }
    return 0; // element not founf
}

int is_in_vec_double(double *a, int el, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] == el)
        {
            return 1; // eLement found
        }
    }
    return 0; // element not founf
}

double vec_sum(double *a, double len){
    double sum = 0;
    for(int i = 0; i < len; i++){
        sum += a[i];
    }

    return sum;
}

int *vec_unique(int *a, int *a_unique_len)
{
    // Initialize the unique array by the size of original array size
    int *a_unique = (int *)malloc(*a_unique_len * sizeof(int));
    // Initialize the unique element counter
    int unique_count = 0;

    for (int i = 0; i < *a_unique_len; i++)
    {
        // If the element not found in unique array, append it and incerement the counter
        if (!is_in_vec(a_unique, a[i], unique_count))
        {
            a_unique[unique_count] = a[i];
            unique_count++;
        }
    }

    // Don't forget to update the unique size value
    *a_unique_len = unique_count;

    // Update the size of unique arrays
    a_unique = (int *)realloc(a_unique, unique_count * sizeof(int));

    return a_unique;
}

double *vec_unique_double(double *a, int *a_unique_len)
{
    // Initialize the unique array by the size of original array size
    double *a_unique = (double *)malloc(*a_unique_len * sizeof(double));
    // Initialize the unique element counter
    int unique_count = 0;

    for (int i = 0; i < *a_unique_len; i++)
    {
        // If the element not found in unique array, append it and incerement the counter
        if (!is_in_vec_double(a_unique, a[i], unique_count))
        {
            a_unique[unique_count] = a[i];
            unique_count++;
        }
    }

    // Don't forget to update the unique size value
    *a_unique_len = unique_count;

    // Update the size of unique arrays
    a_unique = (double *)realloc(a_unique, unique_count * sizeof(double));

    return a_unique;
}

double *vec_divide_int(int *a, int len, int divider)
{
    double *result = (double *)malloc(len * sizeof(double));
    for (int i = 0; i < len; i++)
    {
        result[i] = (double)a[i] / (double)divider;
    }


    return result;
}

int *vec_bincount(int *a, int len, int *a_bincount_len)
{
    // Get all unique values
    int *a_unique = vec_unique(a, a_bincount_len);

    // Initialize a int count dictionary (int : count)
    int *int_counts = (int *)malloc(*a_bincount_len * sizeof(int));

    for (int i = 0; i < *a_bincount_len; i++)
    {
        int_counts[i] = 0;
        for (int j = 0; j < len; j++)
        {
            if (a_unique[i] == a[j])
            {
                int_counts[i]++;
            }
        }
    }

    return int_counts;
}

double *vec_at_column(double **a, int col, int n_samples)
{
    double *result = (double *)malloc(n_samples * sizeof(double));
    for (int i = 0; i < n_samples; i++)
    {
        result[i] = a[i][col];
    }

    return result;
}

#endif