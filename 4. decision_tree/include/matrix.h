#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

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

int *vec_unique(int *a, int len, int *a_unique_len)
{
    // Initialize the unique array by the size of original array size
    int *a_unique = (int *)malloc(len * sizeof(int));
    // Initialize the unique element counter
    int unique_count = 0;

    for (int i = 0; i < len; i++)
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

//---------------------------
// CREATE BINCOUNT
//---------------------------

int *vec_bincount(int *a, int len, int *a_bincount_len)
{
    // Get all unique values
    int *a_unique = vec_unique(a, len, a_bincount_len);

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

#endif