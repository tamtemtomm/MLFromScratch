#include "knn.h"

int main()
{

    double TEST_SIZE = 0.15;
    double K = 2;

    Matrix df = csv_read("dummy.csv", true);
    // matrix_print(&df);

    Matrix train = matrix_slice(&df, 0, df.rows - (int)(TEST_SIZE * df.rows), 0, df.cols);
    Matrix test = matrix_slice(&df, df.rows - (int)(TEST_SIZE *df.rows), df.rows, 0, df.cols);

    Matrix X_train = matrix_slice(&train, 0, train.rows, 0, train.cols-1);
    Matrix X_test = matrix_slice(&test, 0, test.rows, 0, test.cols - 1);
    Matrix y_train = matrix_get_col(&train, train.cols - 1);
    Matrix y_test = matrix_get_col(&test, test.cols - 1);

    KNN model = knn_create(K);
    knn_fit(&model, &X_train, &y_train);
    Matrix predictions = knn_predict(&model, &X_test);
    matrix_print(&predictions);

    return 0;
}