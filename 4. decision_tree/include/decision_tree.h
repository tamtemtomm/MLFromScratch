#ifndef DECIISION_TREE_H
#define DECIISION_TREE_H

#include "node.h"

typedef struct DecisionTree
{
    int max_depth;
    int min_samples_split;
    int tree;

    void (*fit)(struct DecisionTree *, double **, int *, int, int);
    int *(*predict)(struct DecisionTree *, double **, int, int);
};

void fit(DecisionTree *model, double **X, int *y, int n_samples, int n_features)
{
    
}

int *predict(DecisionTree *model, double **X, int n_samples, int n_features)
{
}

DecisionTree create_model(int max_depth, int min_samples_split, int tree)
{
    DecisionTree model;
    model.max_depth = max_depth;
    model.min_samples_split = min_samples_split;
    model.tree = tree;

    model.fit = fit;
    model.predict = predict;

    return model;
}

#endif