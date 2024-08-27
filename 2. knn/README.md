# K-Nearest Neighbors (KNN)

## Overview
This folder contains a C implementation of the K-Nearest Neighbors (KNN) algorithm. The code demonstrates the implementation of a basic KNN model from scratch using standard C libraries. The key functionalities include model training (`fit` function) and prediction (`predict` function).

Reference on Python: [Patrick Loeber](https://www.youtube.com/watch?v=ngLyX54e1LU&list=PLqnslRFeH2Upcrywf-u2etjdxxkL8nl7E)

## Essential Formulas

### 1. Euclidean Distance

The Euclidean distance is used to measure the similarity between two data points. For two points \( \mathbf{a} \) and \( \mathbf{b} \) with \( n \) features, the Euclidean distance \( d \) is computed as:

$$
d(\mathbf{a}, \mathbf{b}) = \sqrt{\sum_{i=1}^{n} (a_i - b_i)^2}
$$

where:
- $$\( \mathbf{a} \)$$ and $$\( \mathbf{b} \)$$ are vectors representing two data points,
- $$\( a_i \)$$ and $$\( b_i \)$$ are the feature values of the \( i \)-th dimension,
- $$\( n \)$$ is the number of features.

### 2. Sorting Distances

To find the k-nearest neighbors, we need to sort the distances between the test point and all training points. The `argsort` function is used to get the indices that would sort the distances array in ascending order.

### 3. Voting Mechanism

Once the k-nearest neighbors are identified, their labels are used to determine the most common label among them. This is often done using a frequency count. The most common label is chosen as the prediction for the test point.

### 4. Frequency Count

To find the most common label among the k-nearest neighbors, a frequency table is created, and the label with the highest count is selected. The function `find_most_common_label` performs this task:

```c
int find_most_common_label(int *labels, int size) {
    LabelCount *label_counts = (LabelCount *)malloc(size * sizeof(LabelCount));
    int unique_labels_count = 0;

    // Initialize label_counts
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < unique_labels_count; j++) {
            if (label_counts[j].label == labels[i]) {
                label_counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            label_counts[unique_labels_count].label = labels[i];
            label_counts[unique_labels_count].count = 1;
            unique_labels_count++;
        }
    }

    // Sort label_counts by count in descending order
    qsort(label_counts, unique_labels_count, sizeof(LabelCount), compare_counter);

    int most_common_label = label_counts[0].label;

    free(label_counts);
    return most_common_label;
}
```

## Files

- **`main.c`**: Contains the main function to create a sample dataset, initialize the model, train it, and make predictions.
- **`knn.h`**: Header file defining the KNN structure and function prototypes.
- **`matrix.h`**: Header file defining matrix operations used in the implementation.
- **`csv.h`**: Header file for CSV reading functions.
- **`counter.h`**: Header file for counting and determining the most common label.
- **`argsort.h`**: Header file for sorting the distance from the shortest.

## Building the Code

To compile the project, navigate to the KNN folder and run:

```bash
gcc -Iinclude -o knn src/main.c
```
This will create an executable named `knn.exe`.

## Running the Code
To run the compiled executable, use:

```bash
./knn.exe
```

## Example Output
The program will output the result of predictions on the test dataset. Example output might look like:
```bash
Iris-setosa
Iris-versicolor
Iris-virginica
...
```

## Usage
1. Create a Sample Dataset: Modify the dataset creation code in main.c to use your own data.
2. Adjust Parameters: Update the number of neighbors 𝐾 and other parameters as needed.
3. Train the Model: Call the fit function to train the model on your data.
4. Make Predictions: Use the predict function to make predictions on new data.

## Notes
1. Ensure you have the required permissions to compile and execute C programs on your system.
2. The implementation assumes that the dataset is already preprocessed and normalized as needed.
