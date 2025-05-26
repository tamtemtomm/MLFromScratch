#include "csv.h"

Matrix* csv_read(const char *filename, bool header)
{
    int rows, cols;
    _csv_inspect_dimension(filename, &rows, &cols);

    if (header)
        rows--;

    FILE *file = fopen(filename, "r");
    Matrix* new_mat = matrix_create(rows, cols);
    char line[1024];
    int r = 0, c = 0;

    // Skip header if necessary
    if (header)
        fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        c = 0;
        while (token)
        {
            matrix_set(new_mat, r, c, atof(token));
            token = strtok(NULL, ",");
            c++;
        }
        r++;
    }

    fclose(file);
    return new_mat;
}
void csv_write(const char *filename, Matrix *mat)
{
    FILE *file = fopen(filename, "w");

    if (!file)
    {
        fprintf(stderr, "Failed to open %s for writing\n", filename);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
        {
            fprintf(file, "%.10g", matrix_get_row_col(mat, i, j));

            if (j < mat->cols - 1)
                fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
void _csv_inspect_dimension(const char *filename, int *rows, int *cols)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        fprintf(stderr, "Failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[1024];
    *rows = 0;
    *cols = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (*rows == 0)
        {
            char *tmp = strdup(line);
            char *token = strtok(tmp, ",");

            while (token)
            {
                (*cols)++;
                token = strtok(NULL, ",");
            }

            free(tmp);
        }
        (*rows)++;
    }

    fclose(file);
}