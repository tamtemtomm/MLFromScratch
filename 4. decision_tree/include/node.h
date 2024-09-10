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
    double **X_right;
    int *y_right;

} DecisionSplit;

typedef struct Node
{
    int feature_index;
    int threshold;

    struct Node *left_tree;
    struct Node *right_tree;

    int value;

    int (*is_leaf_node)(struct Node *);

} Node;

int is_leaf_node(Node *node)
{
    return (node->left_tree == NULL && node->right_tree == NULL);
}

Node create_node_by_value(int value)
{
    Node node;
    node.value = value;
    node.left_tree = NULL;
    node.right_tree = NULL;

    node.is_leaf_node = is_leaf_node;

    return node;
}

Node create_node(int feature_index, int threshold, Node *left_tree, Node *right_tree)
{
    Node node;

    node.feature_index = feature_index;
    node.threshold = threshold;
    node.left_tree = left_tree;
    node.right_tree = right_tree;

    node.is_leaf_node = is_leaf_node;

    // Internal nodes shouldn't have a value assigned, so it can be set to a special value like -1
    node.value = -1;

    return node;
}

void print_tree(Node *tree, int level)
{
    if (tree == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("    "); // Indent
    if (tree->is_leaf_node(tree))
    {
        printf("Leaf node: %d\n", tree->value);
    }
    else
    {
        printf("Feature: %d, Threshold: %d\n", tree->feature_index, tree->threshold);
        print_tree(tree->left_tree, level + 1);
        print_tree(tree->right_tree, level + 1);
    }
}

#endif