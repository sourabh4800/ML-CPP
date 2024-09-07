# K-Nearest Neighbors (KNN) Algorithm in C++

This project implements the K-Nearest Neighbors (KNN) algorithm in C++ to classify the success of companies based on their turnover and team characteristics.

## Features

- Reads data from a CSV file.
- Transforms categorical features to numerical values.
- Calculates distances using Euclidean distance.
- Finds the K nearest neighbors.
- Classifies new data points based on the majority label of their K nearest neighbors.
- Prints the predicted and actual labels for test data points.

### Main Function

The `main` function:
1. Loads the training data from the CSV file.
2. Defines custom test points with actual labels.
3. For each test point, finds the K nearest neighbors and classifies the test point.
4. Prints the predicted label and the actual label for each test point.

## Usage

1. Save the dataset in a file named [`DATA.csv`]
"/cse/Project in c++/DATA.csv".
2. Compile and run the program using the following commands:

```sh
g++ -o knn KNN.cpp
./knn
```
### Output
Test Point: {1256, 87} Predicted label: Successful Actual label: Successful
Test Point: {725, 87} Predicted label: Unsuccessful Actual label: Unsuccessful
Test Point: {1471, 65} Predicted label: Successful Actual label: Successful
Test Point: {703, 130} Predicted label: Unsuccessful Actual label: Unsuccessful
Test Point: {1301, 83} Predicted label: Successful Actual label: Successful