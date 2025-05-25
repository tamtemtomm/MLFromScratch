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
    matrix_free(&(model->weights));
}

void lr_fit(LinearRegression *model, Matrix *X, Matrix *y, double lr, int epochs)
{

    // INPUT
    // X_train = features (m x n)
    // y_train = label (m x 1)

    Matrix X_transpose = matrix_transpose(X);
    double y_mean = matrix_mean(y);
    Matrix dot, dot_error, y_pred, error, grad, grad_lr;

    for (int i = 0; i < epochs; i++)
    {
        y_pred = lr_predict(model, X);

        // Calculate the error
        error = matrix_sub(&y_pred, y); // (m x 1) - (m x 1) => (m x 1)

        // Calculate the gradient
        dot_error = matrix_dot(&X_transpose, &error);  // (n x m) . (m x 1) => (n x 1)
        grad = matrix_div_scalar(&dot_error, X->rows); // (n x 1) / rows => (n x 1)

        // Update weight
        grad_lr = matrix_mult_scalar(&grad, lr);                        // (n x 1) * lr => (n x 1)
        Matrix updated_weights = matrix_sub(&model->weights, &grad_lr); // (n x 1) - (n x 1) => (n x 1)
        matrix_free(&model->weights);
        model->weights = updated_weights;

        // Update bias
        model->bias -= lr * matrix_mean(&error);

        printf("Epoch %d, Loss: %f\n", i + 1, matrix_mse(&y_pred, y)/(y->rows));
        // matrix_print(&y_pred);

        // Free all memory
        matrix_free(&dot_error);
        matrix_free(&grad_lr);
        matrix_free(&error);
        matrix_free(&y_pred);
        matrix_free(&grad);
    }
}

Matrix lr_predict(LinearRegression *model, Matrix *X)
{
    Matrix dot, y_pred;

    // Dot product from the features and weight
    dot = matrix_dot(X, &(model->weights)); // (m x n) . (n x 1) => (m x 1)

    // Add the result with the bias
    y_pred = matrix_add_scalar(&dot, model->bias); // (m x 1) + bias => (m x 1)

    matrix_free(&dot);

    return y_pred;
}
