#include "./../utils/csv/csv.h"

typedef struct
{
    Matrix* X_train;
    Matrix* y_train;

    int k;
} KNN;

KNN knn_create(int k);
void knn_fit(KNN *model, Matrix *X_train, Matrix *y_train);
int knn_predict_one(KNN *model, Matrix *X_test);
Matrix* knn_predict(KNN *model, Matrix *X_test);

