# Neural Network for XOR Problem in C++

This project implements a simple neural network in C++ to solve the XOR problem. The neural network consists of:
- An input layer with 2 neurons
- One hidden layer with 2 neurons
- An output layer with 1 neuron

## Features

- Random initialization of weights and biases
- Sigmoid activation function
- Forward and backward propagation
- Training using gradient descent
- Output printing after every 5000 epochs up to 25000 epochs

## Code Overview

### NeuralNetwork Class

The `NeuralNetwork` class contains the following methods:

- **Constructor**: Initializes weights, biases, and learning rate.
- **sigmoid**: Computes the sigmoid activation function.
- **sigmoid_derivative**: Computes the derivative of the sigmoid function.
- **train**: Trains the network using forward and backward propagation.
- **predict**: Predicts the output for given inputs.

### Main Function

The `main` function:
1. Initializes the neural network with a learning rate of 0.1.
2. Defines the XOR inputs and outputs.
3. Trains the network for 25000 epochs.
4. Prints the outputs after every 5000 epochs.

## Usage

To compile and run the program, use the following commands in your terminal:

```sh
g++ -o neural_network Neural_Network.cpp
./neural_network
```

## Example Output
The program will print the outputs after every 5000 epochs. Here is an example of what the output might look like:
Epoch: 0
Input: 0 0 Output: 0.5
Input: 0 1 Output: 0.5
Input: 1 0 Output: 0.5
Input: 1 1 Output: 0.5

Epoch: 5000
Input: 0 0 Output: 0.01
Input: 0 1 Output: 0.98
Input: 1 0 Output: 0.98
Input: 1 1 Output: 0.02

...

Epoch: 25000
Input: 0 0 Output: 0.01
Input: 0 1 Output: 0.99
Input: 1 0 Output: 0.99
Input: 1 1 Output: 0.01