#include <stdio.h>
#include "./src/linear_regression/linear_regression.h"

int main()
{
    double TEST_SIZE = 0.15;
    double LR = 1e-2;
    int EPOCHS = 1e8;

    Matrix df = csv_read("house_price_regression_dataset.csv", true);
    // matrix_print(&df);

    Matrix train = matrix_slice(&df, 0, df.rows - (int)(TEST_SIZE * df.rows), 0, df.cols);
    Matrix test = matrix_slice(&df, df.rows - (int)(TEST_SIZE * df.rows), df.rows, 0, df.cols);

    Matrix X_train = matrix_slice(&train, 0, train.rows, 0, train.cols - 1);
    Matrix X_test = matrix_slice(&test, 0, test.rows, 0, test.cols - 1);
    Matrix y_train = matrix_get_col(&train, train.cols - 1);
    Matrix y_test = matrix_get_col(&test, test.cols - 1);

    // printf("X_train : \n");
    // matrix_print(&X_train);

    // printf("X_test : \n");
    // matrix_print(&X_test);

    // printf("y_train : \n");
    // matrix_print(&y_train);

    // printf("y_test : \n");
    // matrix_print(&y_test);

    matrix_standardize(&X_train);
    
    LinearRegression model = lr_create(X_train.cols);
    lr_fit(&model, &X_train, &y_train, LR, EPOCHS);
}