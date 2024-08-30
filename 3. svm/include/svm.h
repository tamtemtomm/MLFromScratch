#ifndef SVM_H
#define SVM_H

#include <stdio.h>

typedef struct{
    double lambda;
    double lr;
    int n_iters;
    double *w;
    double *b;

    void (*fit)();
    double *(*predict)();
} SVM;

void fit();
double *predict();


SVM create_model(double lambda, double lr, int n_iters){
    SVM model;
    model.lambda = lambda;
    model.lr = lr;
    model.n_iters = n_iters;
    
    model.fit = fit;
    model.predict = predict;

    printf("Model initialized!\n");
    
    return model;
}

#endif