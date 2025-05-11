#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESION_H

#include "./../utils/csv/csv.h"

typedef struct
{
    Matrix weights;
    double bias;
} LinearRegression;

LinearRegression lr_create(int n_features);
void lr_free(LinearRegression* model);

void lr_fit(LinearRegression *model, Matrix *X, Matrix *y, double lr, int epochs);
Matrix lr_predict(LinearRegression *model, Matrix *X);

#endif