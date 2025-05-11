#include <stdlib.h>
#include <stdio.h>
#include "cnumpy.h"

int main(void)
{
    Matrix mat = matrix_create(3, 2);
    double values[] = {1, 2, 3, 4, 5, 6};
    matrix_set_data(&mat, values);

    Matrix mat_2 = matrix_create(2, 1);
    double values_2[] = {5, 6,};
    matrix_set_data(&mat_2, values_2);

    printf("mat : \n");
    matrix_print(&mat);
    printf("mat 2 : \n");
    matrix_print(&mat_2);

    Matrix mat_dot = matrix_dot(&mat, &mat_2);
    matrix_print(&mat_dot);

    // Matrix mat_random = matrix_random(2, 3);
    // printf("mat random : \n");
    // matrix_print(&mat_random);

    // Matrix mat_col_2 = matrix_get_col(&mat, 1);

    // printf("Rows : %d\n", mat_col_2.rows);
    // printf("Cols : %d\n", mat_col_2.cols);
    // printf("%f\n", matrix_get_row_col(&mat_col_2, 0, 0));

    // matrix_print(&mat_col_2);

    // Matrix mat_new = matrix_add(&mat, &mat_2);
    // matrix_print(&mat_new);

    // printf("%f\n", matrix_total(&mat_new));

    // Matrix mat_transpose = matrix_transpose(&mat);
    // matrix_print(&mat);
    // matrix_print(&mat_transpose);

    // printf("mat var : %f\n", matrix_var(&mat));
    // printf("mat std : %f\n", matrix_std(&mat));
    // printf("%f\n", matrix_dot(&mat, &mat_2));

    // Matrix mat_add_1 = matrix_add_scalar(&mat, 1);
    // matrix_print(&mat_add_1);

    // Matrix mat_dot_1_2 = matrix_dot(&mat, &mat_2);
    // matrix_print(&mat_dot_1_2);

    // Matrix mat_sigmoid = matrix_sigmoid(&mat);
    // matrix_print(&mat_sigmoid);

    // Matrix mat_equal = matrix_equal(&mat, &mat_2);
    // matrix_print(&mat_equal);

    // Matrix mat_hstack = matrix_hstack(&mat, &mat_2);
    // printf("mat_hstack : \n");
    // matrix_print(&mat_hstack);

    matrix_free(&mat);
    matrix_free(&mat_2);

    return 0;
}