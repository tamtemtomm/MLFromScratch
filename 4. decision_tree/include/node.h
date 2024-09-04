#ifndef NODE_H
#define NODE_H

typedef struct DecisionSplit{
    int feature_index;
    int threshold;

    double **X_left;
    double *y_left;
    double *X_right;
    double *Y_right;

} DecisionSplit;

typedef struct Node
{
    double **feature_index;
    double *thresholds;

    struct Node *left;
    struct Node *right;

    int value;

} Node;

Node create_node(int value){
    Node node;
    node.value = value;

    return node;
}

#endif