# Support Vector Machine (SVM)
## Overview
This folder contains a C implementation of the Support Vector Machine (SVM) algorithm. 
The code demonstrates the implementation of a basic SVM model from scratch using standard C libraries. 
The key functionalities include model training (fit function) and prediction (predict function).

## Essential Formula
1. Hinge Loss
   The SVM optimization problem aims to minimize the hinge loss. For a data point
   
   $$
    L(\mathbf{w}, \mathbf{x_i}, y_i) = \max(0, 1 - y_i (\mathbf{w}^T \mathbf{x_i} + b))
   $$
   
    where:
  
  - $$\( \mathbf{w} \)$$ is the weight vector,
  - $$\( \mathbf{x_i} \)$$ is the feature vector of the \( i \)-th sample,
  - $$\( y_i \)$$ is the label of the \( i \)-th sample, either -1 or 1,
  - $$\( b \)$$ is the bias term.

   
2. Support Vector Decision Function
   The decision function for SVM is given by:
  
  $$
     f(\mathbf{x}) = \mathbf{w}^T * \mathbf{x} + b
   $$

3. Optimization Problem
   The optimization objective for linear SVM can be expressed as:

  $$
     \underset{\mathbf{w}, b}{\text{min}} \ \frac{1}{2} \|\mathbf{w}\|^2 + C \sum_{i=1}^{N} \max(0, 1 - y_i (\mathbf{w}^T \mathbf{x}_i + b))
   $$

  Where:
  - 𝐶 is a regularization parameter that controls the trade-off between maximizing the margin and minimizing classification error.

## Files
- `main.c`  : Contains the main function to create a sample dataset, initialize the model, train it, and make predictions.
- `svm.h`   : Header file defining the SVM structure and function prototypes.
- `matrix.h`: Header file defining matrix operations used in the implementation.

## Building the Code
To compile the project, navigate to the SVM folder and run:
```
gcc -Iinclude -o svm src/main.c
```
This will create an executable named `svm.exe`.

## Running the Code 
To run the compiled executable, use:
```
./svm.exe
```

## Usage
1. Create a Sample Dataset: Modify the dataset creation code in `main.c` to use your own data.
2. Adjust Parameters: Update the regularization parameter 𝐶 and other hyperparameters as needed.
3. Train the Model: Call the `fit` function to train the model on your data.
4. Make Predictions: Use the `predict` function to make predictions on new data.

## Notes
1. Ensure you have the required permissions to compile and execute C programs on your system.
2. The implementation assumes that the dataset is already preprocessed and normalized as needed.

