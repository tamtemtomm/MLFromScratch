#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

void mat_vec_mult(const double* mat, const double* vec, double* result, int rows, int cols);
double dot_product(const double* vec1, const double* vec2, int length);
double sum_vector(const double* vec, int length);
void vec_subtract(const double* vec1, const double* vec2, double* result, int length);
void vec_update(double* vec, const double* delta, double lr, int length);

#endif // MATRIX_OPS_H
