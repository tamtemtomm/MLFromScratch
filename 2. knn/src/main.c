#include <stdio.h>
#include <stdlib.h>
#include "knn.h"
#include "csv.h"

#define N_SAMPLES 150
#define N_FEATURES 4
#define LEARNING_RATE 0.1
#define N_ITERS 5000
#define TEST_SIZE 0.15

#define K 3

int main()
{
    // READ CSV ------------------------------------------
    double **X = read_csv("iris.csv", N_SAMPLES, N_FEATURES);
    char **y_str = read_csv_label("iris.csv", N_SAMPLES, N_FEATURES);

    // Change labels into integer
    int *y = (int *)malloc(N_SAMPLES * sizeof(int));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        y[i] = convert_label_string_to_int(y_str[i]);
    }

    // Split dataset
    int test_size = (int)(TEST_SIZE * N_SAMPLES);
    int train_size = N_SAMPLES - test_size;

    double **X_train = (double **)malloc(train_size * sizeof(double *));
    int *y_train = (int *)malloc(train_size * sizeof(int));
    double **X_test = (double **)malloc(test_size * sizeof(double *));
    int *y_test = (int *)malloc(test_size * sizeof(int));

    for (int i = 0; i < train_size; i++)
    {
        X_train[i] = (double *)malloc(N_FEATURES * sizeof(double));
        for (int j = 0; j < N_FEATURES; j++)
        {
            X_train[i][j] = X[i][j];
        }
        y_train[i] = y[i];
    }

    for (int i = 0; i < test_size; i++)
    {
        X_test[i] = (double *)malloc(N_FEATURES * sizeof(double));
        for (int j = 0; j < N_FEATURES; j++)
        {
            X_test[i][j] = X[train_size + i][j];
        }
        y_test[i] = y[train_size + i];
    }

    // Initialize model ----------------------------------
    KNN model = create_model(K);

    // Fit the model into dataset
    model.fit(&model, X_train, y_train, train_size, N_FEATURES);

    // Debug: Print the fitted model's training data
    // for (int i = 0; i < train_size; i++)
    // {
    //     for (int j = 0; j < N_FEATURES; j++)
    //     {
    //         printf("%f|", model.X_train[i][j]);
    //     }
    //     printf("%d\n", model.y_train[i]);
    // }

    // double *distances = get_distances(X_test, X_train, train_size, test_size, N_FEATURES);

    // for (int i = 0; i < train_size; i++)
    // {
    //     printf("%f|", distances[i]);
    // }

    // Predict using model (implement the prediction function to use this)
    // double *result = model.predict(&model, X_test, test_size, N_FEATURES);

    return 0;
}
