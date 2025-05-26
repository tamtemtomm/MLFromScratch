#include "linear_regression.h"

LinearRegression lr_create(int n_features)
{
    LinearRegression model;
    model.weights = matrix_zeros(n_features, 1);
    model.bias = 0.0;

    return model;
}

void lr_free(LinearRegression *model)
{
    matrix_free(model->weights);
}

void lr_fit(LinearRegression *model, Matrix *X, Matrix *y, double lr, int epochs)
{

    // INPUT
    // X_train = features (m x n)
    // y_train = label (m x 1)

    Matrix* X_transpose = matrix_transpose(X);
    Matrix* y_pred;
    Matrix* error;
    Matrix* grad;

    for (int i = 0; i < epochs; i++)
    {
        // Calculate the error
        y_pred = lr_predict(model, X); // (m x 1)
        error = matrix_sub(lr_predict(model, X), y); // (m x 1) - (m x 1) => (m x 1)

        // Calculate the gradient
        grad = matrix_div_scalar(matrix_dot(X_transpose, error), X->rows); // (n x m) . (m x 1) => (n x 1)

        // Update weight
        model->weights = matrix_sub(model->weights, matrix_mult_scalar(grad, lr)); // (n x 1) - (n x 1) => (n x 1);

        // Update bias
        model->bias -= lr * matrix_mean(error);

        printf("Epoch %d, Loss: %f\n", i + 1, matrix_mse(y_pred, y)/(y->rows));
        // matrix_print(&y_pred);

        // Free all memory
        matrix_free(grad);
        matrix_free(error);
        matrix_free(y_pred);
    }
}

Matrix* lr_predict(LinearRegression *model, Matrix *X)
{
    Matrix* dot;
    Matrix* y_pred;

    // Dot product from the features and weight
    dot = matrix_dot(X, model->weights); // (m x n) . (n x 1) => (m x 1)

    // Add the result with the bias
    y_pred = matrix_add_scalar(dot, model->bias); // (m x 1) + bias => (m x 1)

    matrix_free(dot);

    return y_pred;
}
