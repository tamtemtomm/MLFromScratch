import numpy as np

class DecisionTree:
    def __init__(self, max_depth=10, min_samples_split=2):
        self.max_depth = max_depth
        self.min_samples_split = min_samples_split
        self.tree = None

    def fit(self, X, y):
        self.tree = self._grow_tree(X, y)

    def predict(self, X):
        return np.array([self._traverse_tree(x, self.tree) for x in X])

    def _grow_tree(self, X, y, depth=0):
        n_samples, n_features = X.shape
        unique_labels = np.unique(y)

        # Stopping criteria
        if (depth >= self.max_depth or len(unique_labels) == 1 or
                n_samples < self.min_samples_split):
            leaf_value = self._most_common_label(y)
            return Node(value=leaf_value)

        # Find the best split
        best_split = self._best_split(X, y, n_features)
        if not best_split:
            leaf_value = self._most_common_label(y)
            return Node(value=leaf_value)

        left_tree = self._grow_tree(best_split['X_left'], best_split['y_left'], depth + 1)
        right_tree = self._grow_tree(best_split['X_right'], best_split['y_right'], depth + 1)
        return Node(best_split['feature_index'], best_split['threshold'], left_tree, right_tree)

    def _best_split(self, X, y, n_features):
        best_gain = -float('inf')
        split = None

        for feature_index in range(n_features):
            X_column = X[:, feature_index]
            thresholds = np.unique(X_column)

            for threshold in thresholds:
                gain = self._information_gain(y, X_column, threshold)

                if gain > best_gain:
                    best_gain = gain
                    split = {
                        'feature_index': feature_index,
                        'threshold': threshold,
                        'X_left': X[X_column <= threshold],
                        'y_left': y[X_column <= threshold],
                        'X_right': X[X_column > threshold],
                        'y_right': y[X_column > threshold]
                    }

        return split

    def _information_gain(self, y, X_column, threshold):
        parent_entropy = self._entropy(y)

        left_idxs = X_column <= threshold
        right_idxs = X_column > threshold
        if len(y[left_idxs]) == 0 or len(y[right_idxs]) == 0:
            return 0

        n = len(y)
        n_left, n_right = len(y[left_idxs]), len(y[right_idxs])
        e_left, e_right = self._entropy(y[left_idxs]), self._entropy(y[right_idxs])
        child_entropy = (n_left / n) * e_left + (n_right / n) * e_right

        ig = parent_entropy - child_entropy
        return ig

    def _entropy(self, y):
        proportions = np.bincount(y) / len(y)
        return -np.sum([p * np.log2(p) for p in proportions if p > 0])

    def _most_common_label(self, y):
        return np.bincount(y).argmax()

    def _traverse_tree(self, x, node):
        if node.is_leaf_node():
            return node.value

        if x[node.feature_index] <= node.threshold:
            return self._traverse_tree(x, node.left)
        return self._traverse_tree(x, node.right)


class Node:
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, value=None):
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left
        self.right = right
        self.value = value

    def is_leaf_node(self):
        return self.value is not None


# Example usage
if __name__ == "__main__":
    # Example dataset
    X = np.array([[1, 1], [1, 0], [0, 1], [0, 0]])
    y = np.array([1, 1, 0, 0])

    clf = DecisionTree(max_depth=3)
    clf.fit(X, y)
    predictions = clf.predict(X)

    print("Predictions:", predictions)