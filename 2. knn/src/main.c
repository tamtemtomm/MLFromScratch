#include <stdio.h>
#include <stdlib.h>
#include "knn.h"
#include "csv.h"

#define N_SAMPLES 150
#define N_FEATURES 4
#define LEARNING_RATE 0.1
#define N_ITERS 5000

int main()
{

    // READ CSV ------------------------------------------
    double **X = read_csv("iris.csv", 150, 4);
    char **y = read_csv_label("iris.csv", 150, 4);

    // for (int i = 0; i < N_SAMPLES; i++)
    // {
    //     for (int j = 0; j < N_FEATURES; j++)
    //     {
    //         printf("%2lf\n", X[i][j]);
    //     }
    //     printf("%s\n", y[i]);
    // }

    

    return 0;
}