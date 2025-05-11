import numpy as np
from sklearn.model_selection import train_test_split
from sklearn import datasets


class LinearRegression():
    def __init__(self, lr=1e-2, n_iters=1e3):
        self.lr = lr
        self.n_iters = n_iters
        self.weights = None
        self.bias = None

    def fit(self, X, y):
        n_samples, n_features = X.shape

        # init parameters
        self.weights = np.random.randn(n_features)
        self.bias = 0

        # gradient descent
        for _ in range(self.n_iters):
            # (n_samples, n_features) @ (n_features) = (n_samples)
            y_pred = np.dot(X, self.weights) + self.bias

            # compute gradients
            dw = (1 / n_samples) * np.dot(X.T, (y_pred - y))
            db = (1 / n_samples) * np.sum(y_pred - y)

            # update parameters
            self.weights -= self.lr * dw
            self.bias -= self.lr * db

    def predict(self, x):
        return np.dot(x, self.weights) + self.bias


if __name__ == "__main__":
    X, y = datasets.make_regression(n_samples=100, n_features=1, noise=20, random_state=4)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    regressor = LinearRegression(lr=1e-2, n_iters=1000)
    regressor.fit(X_train, y_train)
    y_pred = regressor.predict(X_test)
