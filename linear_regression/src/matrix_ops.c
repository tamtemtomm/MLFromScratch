#include "matrix_ops.h"

void mat_vec_mult(const double* mat, const double* vec, double* result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += mat[i * cols + j] * vec[j];
        }
    }
}

double dot_product(const double* vec1, const double* vec2, int length) {
    double result = 0;
    for (int i = 0; i < length; i++) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

double sum_vector(const double* vec, int length) {
    double result = 0;
    for (int i = 0; i < length; i++) {
        result += vec[i];
    }
    return result;
}

void vec_subtract(const double* vec1, const double* vec2, double* result, int length) {
    for (int i = 0; i < length; i++) {
        result[i] = vec1[i] - vec2[i];
    }
}

void vec_update(double* vec, const double* delta, double lr, int length) {
    for (int i = 0; i < length; i++) {
        vec[i] -= lr * delta[i];
    }
}
