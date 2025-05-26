#ifndef CNUMPY_H
#define CNUMPY_h

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define EULER_NUMBER 2.71828182846

typedef struct
{
    int rows;
    int cols;

    double *data;

} Matrix;

// MATRIX INITIALIZATION
// ---------------------------------------------------------

Matrix* matrix_create(int rows, int cols);
Matrix* matrix_copy(Matrix *mat);
Matrix* matrix_identity(int size);
Matrix* matrix_zeros(int rows, int cols);
Matrix* matrix_random(int rows, int cols);

// MATRIX ATTRIBUTES
// ---------------------------------------------------------

void matrix_free(Matrix *mat);
void matrix_print(Matrix *mat);
double matrix_max(Matrix *mat);
int* matrix_max_idx(Matrix *mat);
double matrix_min(Matrix *mat);
int* matrix_min_idx(Matrix *mat);

// MATRIX SET DATA
// ---------------------------------------------------------

void matrix_set_data(Matrix *mat, double *data);
void matrix_set(Matrix *mat, int row, int col, double value);
void matrix_fill(Matrix *mat, double value);

// MATRIX GET DATA
// ---------------------------------------------------------

double matrix_get_row_col(Matrix *mat, int row, int col);
Matrix* matrix_get_row(Matrix *mat, int row);
Matrix* matrix_get_col(Matrix *mat, int col);

// MATRIX SELF OPERATION
// ---------------------------------------------------------

double matrix_sum(Matrix *mat);
double matrix_mean(Matrix *mat);
double matrix_var(Matrix *mat);
double matrix_std(Matrix *mat);
double matrix_norm(Matrix *mat);
Matrix* matrix_transpose(Matrix *mat);
Matrix* matrix_slice(Matrix *mat, int row_start, int row_end, int col_start, int col_end);

// MATRIX SCALAR OPERATION
// ---------------------------------------------------------

Matrix* matrix_add_scalar(Matrix *mat, double scalar);
Matrix* matrix_sub_scalar(Matrix *mat, double scalar);
Matrix* matrix_mult_scalar(Matrix *mat, double scalar);
Matrix* matrix_div_scalar(Matrix *mat, double scalar);

// MATRIX MATRIX OPERATION
// ---------------------------------------------------------

Matrix* matrix_add(Matrix *mat_a, Matrix *mat_b);
Matrix* matrix_sub(Matrix *mat_a, Matrix *mat_b);
Matrix* matrix_mult(Matrix *mat_a, Matrix *mat_b);
Matrix* matrix_div(Matrix *mat_a, Matrix *mat_b);
Matrix* matrix_dot(Matrix *mat_a, Matrix *mat_b);

// MATRIX LOGICAL OPERATION
// ---------------------------------------------------------
Matrix* matrix_equal(Matrix *mat_a, Matrix *mat_b);
Matrix* matrix_greater(Matrix *mat_a, Matrix *mat_b);
Matrix* matrix_lower(Matrix *mat_a, Matrix *mat_b);
Matrix* matrix_equal_scalar(Matrix *mat, double value);
Matrix* matrix_greater_scalar(Matrix *mat_a, double value);
Matrix* matrix_lower_scalar(Matrix *mat_a, double value);

// MATRIX LOGICAL OPERATION
// ---------------------------------------------------------
Matrix* matrix_hstack(Matrix *mat_a, Matrix *mat_b);
Matrix* matrix_vstack(Matrix *mat_a, Matrix *mat_b);

// MATRIX RESHAPE OPERATION
// ---------------------------------------------------------
Matrix* matrix_reshape(Matrix *mat, int new_rows, int new_cols);
double *matrix_flatten(Matrix *mat);

// MATRIX ACTIVATION OPERATION
// ---------------------------------------------------------

Matrix* matrix_relu(Matrix *mat);
Matrix* matrix_sigmoid(Matrix *mat);
Matrix* matrix_tanh(Matrix *mat);


// MATRIX LOSS OPERATION
// ---------------------------------------------------------

double matrix_mse(Matrix *mat_a, Matrix *mat_b);
void matrix_standardize(Matrix *mat);
double matrix_euclidian_distance(Matrix* a, Matrix*b);
int matrix_unique(Matrix *mat);


// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------
// ---------------------------------------------------------

#endif