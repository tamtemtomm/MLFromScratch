# K-Nearest Neighbors (KNN)

## Overview 
This folder contains a C implementation of the **K-Nearest Neighbors (KNN)** classification algorithm.  
The code demonstrates a basic implementation of KNN from scratch using standard C libraries and a custom matrix library.  
Key functionalities include training (storing the dataset), distance computation, and majority-vote prediction.

Reference in Python: [Patrick Loeber](https://www.youtube.com/watch?v=ngLyX54e1LU&list=PLqnslRFeH2Upcrywf-u2etjdxxkL8nl7E&index=1)

## Essential Concepts

### 1. KNN Model

KNN is a **non-parametric**, **lazy-learning** algorithm.  
It classifies a new data point by looking at the `k` closest training examples in feature space and choosing the most common label among them.

### 2. Euclidean Distance

To measure closeness, the Euclidean distance is used:

$$
\text{distance}(x, x^{(i)}) = \sqrt{ \sum_{j=1}^{n} (x_j - x_j^{(i)})^2 }
$$

Where:
- $x$ is the test sample,
- $x^{(i)}$ is the $i$-th training sample,
- $n$ is the number of features.

### 3. Prediction

1. Compute distance between the test sample and all training samples.  
2. Sort distances and pick the top `k` closest samples.  
3. Perform a **majority vote** among the corresponding labels.  
4. Return the label with the highest vote.

## Files

1. `main.c` : Loads data, splits it, initializes and fits the model, performs prediction, and prints results.  
2. `knn.h` : Defines the `KNN` struct and function prototypes.  
3. `knn.c` : Contains KNN training (`fit`) and prediction (`predict`) logic.  
4. `matrix.h` : Matrix helper functions (assumed pre-written).  
5. `csv.h` : CSV loading utility (assumed pre-written).

## Building and Run the Code

To compile the KNN project:

```bash
./build.bat
```
## Example Output

An example output of the classifier might look like:   

Dataset loaded:
[ [1.0, 2.0, 0.0],
[2.0, 3.0, 0.0],
[6.0, 7.0, 1.0],
[7.0, 8.0, 1.0] ]

Predictions:
[0.0]
[1.0]


## Usage

1. **Prepare Dataset**: Save your labeled dataset in a CSV file where the **last column is the class label**.  
2. **Adjust Parameters**:
   - `TEST_SIZE`: Proportion of data reserved for testing.
   - `K`: Number of neighbors to use for voting.
3. **Compile and Run**: Follow the build and run steps above.
4. **Interpret Results**: The final predictions are printed to stdout.

## Notes

- Currently uses **Euclidean distance** as the metric.
- Handles **numerical labels only**. Consider using a label encoder if working with string labels.
- Designed for educational use and small datasets—performance may degrade with large datasets.
