#include <stdio.h>
#include <stdlib.h>
#include "knn.h"
#include "csv.h"

#define N_SAMPLES 100
#define N_FEATURES 2
#define LEARNING_RATE 0.1
#define N_ITERS 5000

int main(){

    double **X = read_csv("iris.csv", 150, 4);

    for (int i = 0; i< 150; i++){
        for (int j = 0; j < 4; j++){
            printf("%2lf\n",X[i][j]);
            // printf("Hahaha");
        }
    }


    return 0;
}