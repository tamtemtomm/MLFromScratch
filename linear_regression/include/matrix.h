#ifndef MATRIX_H
#define MATRIX_H

void vec_mult(double **data, const double *weight, double *result, int n_samples, int n_features);
double vec_dot(double *vec1, const double *vec2, int length);
double vec_sum(const double *vec, int length);
void vec_subtract(const double *vec1, const double *vec2, double *result, int length);
void vec_update(double *vec, double *w, double lr, int length);
double *vec_at_column(double **X, int column_index, int n_samples);

#endif // MATRIX_H