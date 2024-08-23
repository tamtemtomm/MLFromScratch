# Linear Regression

## Overview 
This folder contains a C implementation of the Linear Regression algorithm. 
The code demonstrates the implementation of a basic Linear Regression model from scratch using standard C libraries. 
The key functionalities include model training (fit function) and prediction (predict function).

Reference on Python : [Patrick Loeber](https://www.youtube.com/watch?v=4swNt7PiamQ&list=PLqnslRFeH2Upcrywf-u2etjdxxkL8nl7E&index=2)

## Essential Formulas

### 1. Linear Model

The linear regression model predicts the target variable $y$ using a linear combination of the input features $X$:

$$
\hat{y} = X \cdot W + b
$$

where:
- $\hat{y}$ is the predicted value,
- $X$ is the matrix of input features,
- $W$ is the vector of weights,
- $b$ is the bias term.

### 2. Loss Function

The model's performance is evaluated using the Mean Squared Error (MSE) loss function:

$$
\text{Loss} = \frac{1}{n} \sum_{i=1}^{n} (\hat{y}_i - y_i)^2
$$

where:
- $n$ is the number of samples,
- $\hat{y}_i$ is the predicted value for sample i \),
- $y_i$ is the actual value for sample \( i \).

### 3. Gradient Descent

To update the weights and bias, gradient descent is used. The gradients of the loss function with respect to the weights \(W\) and bias \(b\) are computed as follows:

Gradient for weights:

$$
\frac{ \partial \text{Loss}}{ \partial W_j} = \frac{1}{n} \sum_{i=1}^{n} (\hat{y}_i - y_i)  (X)_ij
$$

Gradient for bias:

$$
\frac{ \partial \text{Loss}}{\partial b} = \frac{1}{n} \sum_{i=1}^{n} (\hat{y}_i - y_i)
$$


The weights and bias are updated using these gradients:

$$
W_j := W_j - \text{lr} \cdot \frac{\partial \text{Loss}}{\partial W_j}
$$

$$
b := b - \text{lr} \cdot \frac{\partial \text{Loss}}{\partial b}
$$

where:
- `lr` is the learning rate.

## Files
1. `main.c` : Contains the main function to create a sample dataset, initialize the model, train it, and make predictions.
2. `linear_regression.h` : Header file defining the Linear Regression structure and function prototypes.
3. `matrix.h` : Header file defining matrix operations used in the implementation.

### Building the Code
To compile the project, navigate to the linear_regression folder and run
```
gcc -Iinclude -o linear_regression .\src\main.c
```
This will create an executable named `linear_regression.exe`.

### Running the Code
To run the compiled executable, use:
```
./linear_regression.exe
```
### Example Output
The program will output the result of each epoch during training and the final loss value. Example output might look like:
```
Epoch 1
loss : 0.123456
----------------------
...
Epoch 5000
loss : 0.000123
----------------------
RESULT : 
0.456789 | 0.123456 | 0.789123 | ...

```
## Usage
1. Create a Sample Dataset: Modify the dataset creation code in main.c to use your own data.
2. Adjust Parameters: Update the learning rate, number of iterations, and other hyperparameters as needed.
3. Train the Model: Call the fit function to train the model on your data.
4. Make Predictions: Use the predict function to make predictions on new data.

## Notes
1. The implementation uses a fixed learning rate and number of iterations.
2. Ensure you have the required permissions to compile and execute C programs on your system.
