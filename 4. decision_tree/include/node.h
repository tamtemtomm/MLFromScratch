#ifndef NODE_H
#define NODE_H

typedef struct{

    double **feature_index;
    double *thresholds;
    Node* left;
    Node* right;
    int value;

} Node;

#endif