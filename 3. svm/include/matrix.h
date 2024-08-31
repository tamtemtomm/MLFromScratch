#ifndef MATRIX_H
#define MATRIX_H

double vec_dot(double* a, double* b, int length ){
    double sum = 0;
    for (int i = 0; i < length; i++){
        sum += a[i] * b[i];
    }

    return sum;
}

double vec_dot_scalar(double* a, double b, int length ){
    double sum = 0;
    for (int i = 0; i < length; i++){
        sum += a[i] * b;
    }

    return sum;
}

#endif