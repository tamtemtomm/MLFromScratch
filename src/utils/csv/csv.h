#ifndef CSV_H
#define CSV_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "./../cnumpy/cnumpy.h"

Matrix* csv_read(const char *filename, bool header);
void csv_write(const char *filename, Matrix *mat);
void _csv_inspect_dimension(const char *filename, int *rows, int *cols);

#endif