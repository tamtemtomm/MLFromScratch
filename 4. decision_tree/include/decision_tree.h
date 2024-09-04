#ifndef DECIISION_TREE_H
#define DECIISION_TREE_H

#include "node.h"
#include "matrix.h"

typedef struct DecisionTree
{
    int max_depth;
    int min_samples_split;
    // int tree;

    void (*fit)(struct DecisionTree *, double **, int *, int, int);
    int *(*predict)(struct DecisionTree *, double **, int, int);

    Node (*_grow_tree)(struct DecisionTree *, double **, int *, int, int, int);
    DecisionSplit (*_best_split)(struct DecisionTree *, double **, int *, int, int);
    int (*_most_common_label)(struct DecisionTree *, int *, int);

} DecisionTree;

void fit(DecisionTree *model, double **X, int *y, int n_samples, int n_features)
{
}

int *predict(DecisionTree *model, double **X, int n_samples, int n_features)
{
}

Node _grow_tree(DecisionTree *model, double **X, int *y, int depth, int n_samples, int n_features)
{

    // Get unique labels-----------------------------------------
    int unique_features_len = n_samples;
    int *unique_features = vec_unique(y, n_samples, &unique_features_len);

    // DEBUG
    // printf("DEBUG-----\n");
    // for (int i = 0; i < unique_features_len; i++)
    // {
    //     printf("%d\n", n_unique_features);
    //     printf("Unique %d : %d\n", i, unique_features[i]);
    // }

    // Stopping criteria
    if (depth >= model->max_depth || unique_features_len == 1 || n_samples < model->min_samples_split)
    {
        int leaf_value = model->_most_common_label(model, y, n_samples);
        return create_node(leaf_value);
    }

    // Find the best split
}

DecisionSplit _best_split(DecisionTree *model, double **X, int *y, int n_samples, int n_features)
{   
    
}

int _most_common_label(DecisionTree *model, int *y, int n_samples)
{
    int bincount_len = n_samples;
    int *bincount = vec_bincount(y, n_samples, &bincount_len);
    int argmax = vec_argmax(bincount, bincount_len);

    // DEBUG
    // printf("DEBUG-----\n");
    // for (int i = 0; i < bincount_len; i++) {
    //     printf("count : %d\n", bincount[i]);
    // }
    // printf("%d\n", argmax);

    return argmax;
}

DecisionTree create_model(int max_depth, int min_samples_split)
{
    DecisionTree model;
    model.max_depth = max_depth;
    model.min_samples_split = min_samples_split;

    model.fit = fit;
    model.predict = predict;

    model._grow_tree = _grow_tree;
    model._most_common_label = _most_common_label;

    return model;
}

#endif