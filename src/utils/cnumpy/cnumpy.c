#include "cnumpy.h"

// MATRIX ERROR
// ---------------------------------------------------------
void matrix_dimension_mismatch(Matrix *mat_a, Matrix *mat_b)
{
    fprintf(stderr, "Dimension mismatch : (%d : %d) & (%d : %d)", mat_a->rows, mat_a->cols, mat_b->rows, mat_b->cols);
    exit(EXIT_FAILURE);
}

// MATRIX INITIALIZATION
// ---------------------------------------------------------

Matrix *matrix_create(int rows, int cols)
{
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
    if (mat == NULL)
        return NULL;

    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double *)calloc(rows * cols, sizeof(double));

    if (mat->data == NULL)
    {
        free(mat);
        return NULL;
    }

    return mat;
}
Matrix *matrix_copy(Matrix *mat)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j, matrix_get_row_col(mat, i, j));
        }
    }

    return new_mat;
}
Matrix *matrix_identity(int size)
{
    Matrix *new_mat = matrix_create(size, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                matrix_set(new_mat, i, j, 1.0);
            else
                matrix_set(new_mat, i, j, 0.0);
        }
    }

    return new_mat;
}
Matrix *matrix_zeros(int rows, int cols)
{
    Matrix *new_mat = matrix_create(rows, cols);
    matrix_fill(new_mat, 0);

    return new_mat;
}
Matrix *matrix_random(int rows, int cols)
{
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    Matrix *new_mat = matrix_create(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix_set(new_mat, i, j, (double)rand() / RAND_MAX);
        }
    }

    return new_mat;
}

// MATRIX ATTRIBUTES
// ---------------------------------------------------------

void matrix_free(Matrix *mat)
{
    free(mat->data);
    mat->data = NULL;
}
void matrix_print(Matrix *mat)
{
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            printf("%f | ", matrix_get_row_col(mat, i, j));
        }
        printf("\n");
    }
}
double matrix_max(Matrix *mat)
{
    double max = -INFINITY;
    double cur_value;

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            cur_value = matrix_get_row_col(mat, i, j);
            if (cur_value > max)
                max = cur_value;
        }
    }

    return max;
}

int *matrix_max_idx(Matrix *mat)
{
    double max = -INFINITY;
    double cur_value;
    int *res = malloc(2 * sizeof(int));
    res[0] = 0;
    res[1] = 0;

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            cur_value = matrix_get_row_col(mat, i, j);
            if (cur_value > max)
            {
                max = cur_value;
                res[0] = i;
                res[1] = j;
            }
        }
    }

    return res;
}

double matrix_min(Matrix *mat)
{
    double min = INFINITY;
    double cur_value;

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            cur_value = matrix_get_row_col(mat, i, j);
            if (cur_value < min)
                min = cur_value;
        }
    }

    return min;
}

int *matrix_min_idx(Matrix *mat)
{
    double min = INFINITY;
    double cur_value;
    int *res = malloc(2 * sizeof(int));
    res[0] = 0;
    res[1] = 0;

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            cur_value = matrix_get_row_col(mat, i, j);
            if (cur_value < min)
            {
                min = cur_value;
                res[0] = i;
                res[1] = j;
            }
        }
    }

    return res;
}

// MATRIX SET DATA
// ---------------------------------------------------------

void matrix_set_data(Matrix *mat, double *data)
{
    int size = mat->rows * mat->cols;
    for (int i = 0; i < size; i++)
    {
        mat->data[i] = data[i];
    }
}
void matrix_set(Matrix *mat, int row, int col, double value)
{
    mat->data[row * mat->cols + col] = value;
}
void matrix_fill(Matrix *mat, double value)
{
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(mat, i, j, value);
        }
    }
}

// MATRIX GET DATA
// ---------------------------------------------------------

double matrix_get_row_col(Matrix *mat, int row, int col)
{
    if (row < 0 || row >= mat->rows)
    {
        fprintf(stderr, "The matrix only have %d rows\n", mat->rows);
    }

    if (col < 0 || col >= mat->cols)
    {
        fprintf(stderr, "The matrix only have %d cols\n", mat->cols);
    }

    return mat->data[row * mat->cols + col];
}
Matrix *matrix_get_row(Matrix *mat, int row)
{
    if (row < 0 || row >= mat->rows)
    {
        fprintf(stderr, "Error : Row index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    Matrix *row_matrix = matrix_create(1, mat->cols);

    for (int col = 0; col < mat->cols; col++)
    {
        row_matrix->data[col] = mat->data[row * mat->cols + col];
    }

    return row_matrix;
}
Matrix *matrix_get_col(Matrix *mat, int col)
{
    if (col < 0 || col >= mat->cols)
    {
        fprintf(stderr, "Error : Col index out of bounds");
        exit(EXIT_FAILURE);
    }

    Matrix *col_matrix = matrix_create(mat->rows, 1);

    for (int row = 0; row < mat->rows; row++)
    {
        col_matrix->data[row] = mat->data[row * mat->cols + col];
    }

    return col_matrix;
}

// MATRIX SELF OPERATION
// ---------------------------------------------------------

double matrix_sum(Matrix *mat)
{
    double total = 0;
    int size = mat->rows * mat->cols;
    for (int i = 0; i < size; i++)
    {
        total += mat->data[i];
    }

    return total;
}
double matrix_mean(Matrix *mat)
{
    return matrix_sum(mat) / (mat->rows * mat->cols);
}
double matrix_var(Matrix *mat)
{
    double squared_loss = 0;
    double mean = matrix_mean(mat);

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            double diff = matrix_get_row_col(mat, i, j) - mean;
            squared_loss += diff * diff;
        }
    }

    return mean / (mat->rows * mat->cols);
}
double matrix_std(Matrix *mat)
{
    return sqrt(matrix_var(mat));
}
double matrix_norm(Matrix *mat)
{
    double sum = 0;

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            double value = matrix_get_row_col(mat, i, j);
            sum += value * value;
        }
    }

    return sqrt(sum);
}
Matrix *matrix_transpose(Matrix *mat)
{
    Matrix *mat_new = matrix_create(mat->cols, mat->rows);
    double value;

    for (int i = 0; i < mat_new->rows; i++)
    {
        for (int j = 0; j < mat_new->cols; j++)
        {
            value = matrix_get_row_col(mat, j, i);
            matrix_set(mat_new, i, j, value);
        }
    }

    return mat_new;
}
Matrix *matrix_slice(Matrix *mat, int row_start, int row_end, int col_start, int col_end)
{
    if (row_start < 0 || row_end > mat->rows || col_start < 0 || col_end > mat->cols || row_start >= row_end || col_start >= col_end)
    {
        fprintf(stderr, "Error : Invalid slice indices\n");
        exit(EXIT_FAILURE);
    }

    int new_rows = row_end - row_start;
    int new_cols = col_end - col_start;

    Matrix *submat = matrix_create(new_rows, new_cols);

    for (int i = 0; i < new_rows; i++)
    {
        for (int j = 0; j < new_cols; j++)
        {
            matrix_set(submat, i, j, matrix_get_row_col(mat, row_start + i, col_start + j));
        }
    }

    return submat;
}

// MATRIX SCALAR OPERATION
// ---------------------------------------------------------
Matrix *matrix_add_scalar(Matrix *mat, double scalar)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j, matrix_get_row_col(mat, i, j) + scalar);
        }
    }

    return new_mat;
}
Matrix *matrix_sub_scalar(Matrix *mat, double scalar)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j, matrix_get_row_col(mat, i, j) - scalar);
        }
    }

    return new_mat;
}
Matrix *matrix_mult_scalar(Matrix *mat, double scalar)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j, matrix_get_row_col(mat, i, j) * scalar);
        }
    }

    return new_mat;
}
Matrix *matrix_div_scalar(Matrix *mat, double scalar)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j, matrix_get_row_col(mat, i, j) / scalar);
        }
    }

    return new_mat;
}

// MATRIX MATRIX OPERATION
// ---------------------------------------------------------

Matrix *matrix_add(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows || mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    matrix_dimension_mismatch(mat_a, mat_b);

    Matrix *new_mat = matrix_create(mat_a->rows, mat_b->cols);
    for (int i = 0; i < new_mat->rows; i++)
    {
        for (int j = 0; j < new_mat->cols; j++)
        {
            matrix_set(new_mat, i, j,
                       matrix_get_row_col(mat_a, i, j) + matrix_get_row_col(mat_b, i, j));
        }
    }

    return new_mat;
}
Matrix *matrix_sub(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows || mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *new_mat = matrix_create(mat_a->rows, mat_b->cols);
    for (int i = 0; i < new_mat->rows; i++)
    {
        for (int j = 0; j < new_mat->cols; j++)
        {
            matrix_set(new_mat, i, j,
                       matrix_get_row_col(mat_a, i, j) - matrix_get_row_col(mat_b, i, j));
        }
    }

    return new_mat;
}
Matrix *matrix_mult(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows || mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *new_mat = matrix_create(mat_a->rows, mat_b->cols);
    for (int i = 0; i < new_mat->rows; i++)
    {
        for (int j = 0; j < new_mat->cols; j++)
        {
            matrix_set(new_mat, i, j,
                       matrix_get_row_col(mat_a, i, j) * matrix_get_row_col(mat_b, i, j));
        }
    }

    return new_mat;
}
Matrix *matrix_div(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows || mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *mat_new = matrix_create(mat_a->rows, mat_b->cols);
    for (int i = 0; i < mat_a->rows; i++)
    {
        for (int j = 0; j < mat_a->cols; j++)
        {
            matrix_set(mat_new, i, j,
                       matrix_get_row_col(mat_a, i, j) / matrix_get_row_col(mat_b, i, j));
        }
    }

    return mat_new;
}
Matrix *matrix_dot(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->cols != mat_b->rows)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *new_mat = matrix_create(mat_a->rows, mat_b->cols);

    for (int i = 0; i < mat_a->rows; i++)
    {
        for (int j = 0; j < mat_b->cols; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < mat_a->cols; k++)
            {
                sum += matrix_get_row_col(mat_a, i, k) * matrix_get_row_col(mat_b, k, j);
            }
            matrix_set(new_mat, i, j, sum);
        }
    }

    return new_mat;
}

// MATRIX ACTIVATION OPERATION
// ---------------------------------------------------------

Matrix *matrix_relu(Matrix *mat)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);
    double value, new_value = 0;

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            value = matrix_get_row_col(mat, i, j);
            new_value = value > 0 ? value : 0;
            matrix_set(new_mat, i, j, new_value);
        }
    }

    return new_mat;
}
Matrix *matrix_sigmoid(Matrix *mat)
{

    Matrix *new_mat = matrix_create(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j,
                       1 / (1 + pow(EULER_NUMBER, -matrix_get_row_col(mat, i, j))));
        }
    }

    return new_mat;
}
Matrix *matrix_tanh(Matrix *mat)
{

    Matrix *new_mat = matrix_create(mat->rows, mat->cols);
    double value, tanh_value;

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            value = matrix_get_row_col(mat, i, j);
            tanh_value = (pow(EULER_NUMBER, value) - pow(EULER_NUMBER, -value)) /
                         (pow(EULER_NUMBER, value) + pow(EULER_NUMBER, -value));

            matrix_set(new_mat, i, j, tanh_value);
        }
    }

    return new_mat;
}

// MATRIX LOGICAL OPERATION
// ---------------------------------------------------------

Matrix *matrix_equal(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows || mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *new_mat = matrix_create(mat_a->rows, mat_a->cols);

    for (int i = 0; i < new_mat->rows; i++)
    {
        for (int j = 0; j < new_mat->cols; j++)
        {
            matrix_set(new_mat, i, j,
                       matrix_get_row_col(mat_a, i, j) == matrix_get_row_col(mat_b, i, j) ? 1 : 0);
        }
    }

    return new_mat;
}
Matrix *matrix_greater(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows || mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *new_mat = matrix_create(mat_a->rows, mat_a->cols);
    for (int i = 0; i < new_mat->rows; i++)
    {
        for (int j = 0; j < new_mat->cols; j++)
        {
            matrix_set(new_mat, i, j,
                       matrix_get_row_col(mat_a, i, j) > matrix_get_row_col(mat_b, i, j) ? 1 : 0);
        }
    }

    return new_mat;
}
Matrix *matrix_lower(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows || mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *new_mat = matrix_create(mat_a->rows, mat_a->cols);

    for (int i = 0; i < new_mat->rows; i++)
    {
        for (int j = 0; j < new_mat->cols; j++)
        {
            matrix_set(new_mat, i, j,
                       matrix_get_row_col(mat_a, i, j) < matrix_get_row_col(mat_b, i, j) ? 1 : 0);
        }
    }

    return new_mat;
}
Matrix *matrix_equal_scalar(Matrix *mat, double value)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j, matrix_get_row_col(mat, i, j) == value ? 1 : 0);
        }
    }

    return new_mat;
}
Matrix *matrix_greater_scalar(Matrix *mat, double value)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j, matrix_get_row_col(mat, i, j) > value ? 1 : 0);
        }
    }

    return new_mat;
}
Matrix *matrix_lower_scalar(Matrix *mat, double value)
{
    Matrix *new_mat = matrix_create(mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            matrix_set(new_mat, i, j, matrix_get_row_col(mat, i, j) < value ? 1 : 0);
        }
    }

    return new_mat;
}

// MATRIX LOGICAL OPERATION
// ---------------------------------------------------------
Matrix *matrix_hstack(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *new_mat = matrix_create(mat_a->rows, mat_a->cols + mat_b->cols);

    for (int i = 0; i < new_mat->rows; i++)
    {
        for (int j = 0; j < new_mat->cols; j++)
        {
            if (j < mat_a->cols)
                matrix_set(new_mat, i, j, matrix_get_row_col(mat_a, i, j));
            else
                matrix_set(new_mat, i, j, matrix_get_row_col(mat_b, i, j - mat_a->cols));
        }
    }

    return new_mat;
}
Matrix *matrix_vstack(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    Matrix *new_mat = matrix_create(mat_a->rows + mat_b->rows, mat_a->cols);

    for (int i = 0; i < new_mat->rows; i++)
    {
        for (int j = 0; j < new_mat->cols; j++)
        {
            if (i < mat_a->rows)
                matrix_set(new_mat, i, j, matrix_get_row_col(mat_a, i, j));
            else
                matrix_set(new_mat, i, j, matrix_get_row_col(mat_b, i - mat_a->rows, j));
        }
    }

    return new_mat;
}

// MATRIX RESHAPE OPERATION
// ---------------------------------------------------------
Matrix *matrix_reshape(Matrix *mat, int new_rows, int new_cols)
{
    if (mat->rows * mat->cols != new_rows * new_cols)
    {
        fprintf(stderr, "Dimension mismatch ; (%d x %d) & (%d x %d)",
                mat->rows, mat->cols, new_rows, new_cols);
        exit(EXIT_FAILURE);
    }

    Matrix *new_mat = matrix_create(new_rows, new_cols);
    int size = new_rows * new_cols;

    for (int i = 0; i < size; i++)
    {
        new_mat->data[i] = mat->data[i];
    }

    return new_mat;
}
double *matrix_flatten(Matrix *mat)
{
    int size = mat->rows * mat->cols;
    double *flat = malloc(sizeof(double) * size);

    for (int i = 0; i < size; i++)
    {
        flat[i] = mat->data[i];
    }

    return flat;
}

// MATRIX LOSS OPERATION
// ---------------------------------------------------------

double matrix_mse(Matrix *mat_a, Matrix *mat_b)
{
    if (mat_a->rows != mat_b->rows || mat_a->cols != mat_b->cols)
    {
        matrix_dimension_mismatch(mat_a, mat_b);
    }

    double sum = 0;
    double value;

    for (int i = 0; i < mat_a->rows; i++)
    {
        for (int j = 0; j < mat_a->cols; j++)
        {
            value = matrix_get_row_col(mat_a, i, j) - matrix_get_row_col(mat_b, i, j);
            sum += pow(value, 2);
        }
    }

    return sum / (mat_a->rows * mat_b->cols);
}
void matrix_standardize(Matrix *mat)
{
    for (int j = 0; j < mat->cols; j++)
    {
        double mean = 0.0;
        double std = 0.0;

        // Compute mean
        for (int i = 0; i < mat->rows; i++)
            mean += matrix_get_row_col(mat, i, j);
        mean /= mat->rows;

        // Compute std
        for (int i = 0; i < mat->rows; i++)
            std += pow(matrix_get_row_col(mat, i, j) - mean, 2);
        std = sqrt(std / mat->rows);

        // Standardize
        for (int i = 0; i < mat->rows; i++)
        {
            double val = matrix_get_row_col(mat, i, j);
            val = (val - mean) / (std + 1e-8); // Avoid divide by 0
            matrix_set(mat, i, j, val);
        }
    }
}

// MATRIX DISTANCE OPERATION
// ---------------------------------------------------------
double matrix_euclidian_distance(Matrix *a, Matrix *b)
{
    double sum = 0.0;
    if (a->rows != b->rows || a->cols != b->cols)
    {
        matrix_dimension_mismatch(a, b);
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            double diff = matrix_get_row_col(a, i, j) - matrix_get_row_col(b, i, j);
            sum += diff * diff;
        }
    }

    return sqrt(sum);
}

bool is_close(double a, double b)
{
    return fabs(a - b) < 1e-9;
}

int matrix_unique(Matrix *mat)
{
    int count = 0;
    int capacity = 16;
    double *seen = malloc(capacity * sizeof(double));

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            double val = matrix_get_row_col(mat, i, j);
            bool found = false;

            for (int k = 0; k < count; k++)
            {
                if (is_close(val, seen[k]))
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                if (count >= capacity)
                {
                    capacity *= 2;
                    seen = realloc(seen, capacity * sizeof(double));
                }
                seen[count++] = val;
            }
        }
    }

    free(seen);
    return count;
}
