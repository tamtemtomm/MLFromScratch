#ifndef DECIISION_TREE_H
#define DECIISION_TREE_H

#include <math.h>

#include "node.h"
#include "matrix.h"

typedef struct DecisionTree
{
    int max_depth;
    int min_samples_split;
    Node tree;
    // int tree;

    void (*fit)(struct DecisionTree *, double **, int *, int, int);
    int *(*predict)(struct DecisionTree *, double **, int, int);

    Node (*_grow_tree)(struct DecisionTree *, double **, int *, int, int, int);
    DecisionSplit (*_best_split)(struct DecisionTree *, double **, int *, int, int);

    double (*_information_gain)(struct DecisionTree *, int *, double *, double, int);
    double (*_entropy)(struct DecisionTree *, int *, int len);
    int (*_most_common_label)(struct DecisionTree *, int *, int);

} DecisionTree;

void fit(DecisionTree *model, double **X, int *y, int n_samples, int n_features)
{
    model->tree = model->_grow_tree(model, X, y, 0, n_samples, n_features);
}

int *predict(DecisionTree *model, double **X, int n_samples, int n_features)
{
}

Node _grow_tree(DecisionTree *model, double **X, int *y, int depth, int n_samples, int n_features)
{

    // Get unique labels-----------------------------------------
    int unique_features_len = n_samples;
    int *unique_features = vec_unique(y, &unique_features_len);

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
        return create_node_by_value(leaf_value);
    }

    // Find the best split
    DecisionSplit best_split = model->_best_split(model, X, y, n_samples, n_features);

    Node left_tree = model->_grow_tree(model, best_split.X_left, best_split.y_left, depth + 1, best_split.left_len, n_features);
    Node right_tree = model->_grow_tree(model, best_split.X_right, best_split.y_right, depth + 1, best_split.right_len, n_features);

    return create_node(best_split.feature_index, best_split.threshold, &left_tree, &right_tree);
}

DecisionSplit _best_split(DecisionTree *model, double **X, int *y, int n_samples, int n_features)
{
    double best_gain = -(double)INFINITY;
    DecisionSplit split = {0};

    for (int feature_index = 0; feature_index < n_features; feature_index++)
    {
        double *X_column = vec_at_column(X, feature_index, n_samples);

        int threshold_len = n_samples;
        double *thresholds = vec_unique_double(X_column, &threshold_len);

        for (int threshold_index = 0; threshold_index < threshold_len; threshold_index++)
        {

            double gain = model->_information_gain(model, y, X_column, thresholds[threshold_index], n_samples);
            if (gain > best_gain)
            {
                best_gain = gain;
                double **X_left = (double **)malloc(n_samples * sizeof(double *));
                double **X_right = (double **)malloc(n_samples * sizeof(double *));
                for (int i = 0; i < n_samples; i++)
                {
                    X_left[i] = (double *)malloc(n_samples * sizeof(double));
                    X_right[i] = (double *)malloc(n_samples * sizeof(double));
                }
    
                int *y_left = (int *)malloc(n_samples * sizeof(int));
                int *y_right = (int *)malloc(n_samples * sizeof(int));

                int left_values_len = 0, right_values_len = 0; // Initialize these correctly

                for (int i = 0; i < n_samples; i++)
                {
                    if (X_column[i] <= thresholds[threshold_index])
                    {
                        X_left[left_values_len] = X[i];
                        y_left[left_values_len] = y[i];
                        left_values_len++;
                    }
                    else
                    {
                        X_right[right_values_len] = X[i];
                        y_right[right_values_len] = y[i];
                        right_values_len++;
                    }
                }

                X_left = (double **)realloc(X_left, left_values_len * sizeof(double *));
                y_left = (int *)realloc(y_left, left_values_len * sizeof(int));
                X_right = (double **)realloc(X_right, right_values_len * sizeof(double *));
                y_right = (int *)realloc(y_right, right_values_len * sizeof(int));

                split.feature_index = feature_index;
                split.threshold = thresholds[threshold_index];

                split.left_len = left_values_len;
                split.right_len = right_values_len;

                split.X_left = X_left;
                split.X_right = X_right;
                split.y_left = y_left;
                split.y_right = y_right;
            }
        }
        free(thresholds);
        free(X_column);
    }

    return split;
}

double _information_gain(DecisionTree *model, int *y, double *X_column, double threshold, int n_samples)
{
    printf("Calculating information gain for threshold %f\n", threshold);

    double parent_entropy = model->_entropy(model, y, n_samples);

    int *left_values = (int *)malloc(n_samples * sizeof(int));
    int *right_values = (int *)malloc(n_samples * sizeof(int));
    int left_values_len = 0, right_values_len = 0; // Initialize these correctly

    for (int i = 0; i < n_samples; i++)
    {
        if (X_column[i] <= threshold)
        {
            left_values[left_values_len] = y[i];
            left_values_len++;
        }
        else
        {
            right_values[right_values_len] = y[i];
            right_values_len++;
        }
    }

    if (left_values_len == 0.0f || right_values_len == 0.0f || left_values_len == -0.0f || right_values_len == -0.0f)
    {
        printf("No split occurred, returning gain = 0\n");
        return 0.0;
    }

    double left_entropy = model->_entropy(model, left_values, left_values_len);
    double right_entropy = model->_entropy(model, right_values, right_values_len);

    double child_entropy = (((double)left_values_len / n_samples) * left_entropy) +
                           (((double)right_values_len / n_samples) * right_entropy);

    double ig = parent_entropy - child_entropy;
    printf("Parent entropy: %f, Left entropy: %f, Right entropy: %f, Information Gain: %f\n", parent_entropy, left_entropy, right_entropy, ig);

    free(left_values);
    free(right_values);
    return ig;
}

double _entropy(DecisionTree *model, int *y, int len)
{
    int bincount_len = len;
    int *bincount = vec_bincount(y, len, &bincount_len);
    double *proportions = vec_divide_int(bincount, bincount_len, len);

    double sum = 0.0;
    for (int i = 0; i < bincount_len; i++)
    {
        // printf("%d\n", bincount[i]);
        // printf("%f\n", log2f(proportions[i]));
        if (proportions[i] > 0)
        {
            sum += proportions[i] * log2f(proportions[i]);
        }
    }

    // DEBUG
    // printf("DEBUG------\n");
    // for (int i = 0; i < bincount_len; i++)
    // {
    //     printf("%d\n", bincount[i]);
    //     printf("%f\n", proportion[i]);
    // }

    return -sum;
}

int _most_common_label(DecisionTree *model, int *y, int n_samples)
{
    int bincount_len = n_samples;
    int *bincount = vec_bincount(y, n_samples, &bincount_len);
    int argmax = vec_argmax(bincount, bincount_len);

    // DEBUG
    printf("DEBUG-----\n");
    for (int i = 0; i < bincount_len; i++)
    {
        printf("count : %d\n", bincount[i]);
    }
    printf("%d\n", argmax);

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
    model._best_split = _best_split;

    model._information_gain = _information_gain;
    model._entropy = _entropy;
    model._most_common_label = _most_common_label;

    return model;
}

#endif