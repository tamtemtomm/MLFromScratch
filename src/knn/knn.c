#include "knn.h"

KNN knn_create(int k){
    KNN model;
    model.k = k;
    model.X_train = matrix_create(0, 0); // Initialize with empty matrix
    model.y_train = matrix_create(0, 0); // Initialize with empty matrix
    return model;
}

void knn_fit(KNN *model, Matrix *X_train, Matrix *y_train){

    model->X_train = matrix_copy(X_train);
    model->y_train = matrix_copy(y_train);

}

int knn_predict_one(KNN *model, Matrix *X_test){
    if (X_test->cols != model->X_train->cols){
        fprintf(stderr, "Error: Number of features in test data does not match data training");
        exit(EXIT_FAILURE);
    }

    if (X_test->rows != 1){
        fprintf(stderr, "Error: Test data must be a single row (1D arrray)");
        exit(EXIT_FAILURE);
    }

    int m = model->X_train->rows;
    int n = model->X_train->cols;

    Matrix* distances = matrix_create(m, 1);

    for (int i = 0; i < m; i++){

        Matrix* row = matrix_get_row(model->X_train, i);

        matrix_set(distances, i, 0, matrix_euclidian_distance(X_test, row));

        free(row->data); // Free the row matrix after use
    }

    Matrix* neighbor_indices = matrix_create(model->k, 1);

    for (int i = 0; i < model->k; i++){

        double min_dist = INFINITY;
        int min_idx = -1;

        for (int j = 0; j < m; j++){
            if (matrix_get_row_col(distances, j, 0) < min_dist){
                min_dist = matrix_get_row_col(distances, j, 0);
                min_idx = j;
            }
        }

        neighbor_indices->data[i] = min_idx;
        matrix_set(distances, min_idx, 0, INFINITY);
    }

    // Vote labels
    Matrix* votes = matrix_zeros(matrix_unique(model->y_train), 1);
    for (int i = 0; i < model->k; i++){
        int idx = (int)matrix_get_row_col(neighbor_indices, i, 0);
        int label = (int)matrix_get_row_col(model->y_train, idx, 0);
        matrix_set(votes, label, 0, matrix_get_row_col(votes, label, 0) + 1);
    }

    return matrix_max_idx(votes)[0]; // Return the index of the maximum vote
}

Matrix* knn_predict(KNN *model, Matrix *X_test){
    Matrix* y_pred = matrix_create(X_test->rows, 1);
    for (int i = 0; i < X_test->rows; i++){
        Matrix* row = matrix_get_row(X_test, i);
        int pred = knn_predict_one(model, row);
        matrix_set(y_pred, i, 0, (double)pred);

        free(row->data); // ADD THIS
    }

    return y_pred;
}
