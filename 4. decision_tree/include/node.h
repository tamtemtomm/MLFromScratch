#ifndef NODE_H
#define NODE_H

typedef struct DecisionSplit
{
    int feature_index;
    int threshold;

    int left_len;
    int right_len;

    double **X_left;
    int *y_left;
    double *X_right;
    int *y_right;

} DecisionSplit;

typedef struct Node
{
    int feature_index;
    int threshold;

    struct Node *left_tree;
    struct Node *right_tree;

    int value;

} Node;

Node create_node_by_value(int value)
{
    Node node;
    node.value = value;

    return node;
}

Node create_node(int feature_index, int threshold, DecisionSplit *left_tree, DecisionSplit *right_tree)
{
    Node node;

    node.feature_index = feature_index;
    node.threshold = threshold;
    node.left_tree = left_tree;
    node.right_tree = right_tree;

    return node;
}

#endif