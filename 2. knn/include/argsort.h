#ifndef ARGSORT_H
#define ARGSORT_H

#include <math.h>
#include <stdlib.h>

typedef struct
{
    double value;
    int index;
} IndexedValue;

// Comparison function for sorting IndexedValue array
int compare_argsort(const void *a, const void *b)
{
    double diff = ((IndexedValue *)a)->value - ((IndexedValue *)b)->value;
    return (diff > 0) - (diff < 0);
}

void argsort(double *arr, int *indices, int n)
{
    IndexedValue *indexedArray = (IndexedValue *)malloc(n * sizeof(IndexedValue));

    // Fill IndexedValue array
    for (int i = 0; i < n; i++)
    {
        indexedArray[i].value = arr[i];
        indexedArray[i].index = i;
    }

    // Sort IndexedValue array by value
    qsort(indexedArray, n, sizeof(IndexedValue), compare_argsort);

    // Extract sorted indices
    for (int i = 0; i < n; i++)
    {
        indices[i] = indexedArray[i].index;
    }

    // Free allocated memory
    free(indexedArray);
}
#endif