#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class NeuralNetwork {
private:
    vector<vector<double>> weights1;
    vector<double> weights2;
    vector<double> bias1;
    double bias2;
    double learning_rate;

    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    double sigmoid_derivative(double x) {
        return x * (1.0 - x);
    }

public:
    NeuralNetwork(double lr) : learning_rate(lr) {
        srand(time(0));
        weights1 = {{(double)rand() / RAND_MAX, (double)rand() / RAND_MAX},
                    {(double)rand() / RAND_MAX, (double)rand() / RAND_MAX}};
        weights2 = {(double)rand() / RAND_MAX, (double)rand() / RAND_MAX};
        bias1 = {(double)rand() / RAND_MAX, (double)rand() / RAND_MAX};
        bias2 = (double)rand() / RAND_MAX;
    }

    double train(vector<double> inputs, double target) {
        // Forward propagation
        vector<double> hidden_layer_output(2);
        for (int i = 0; i < 2; ++i) {
            hidden_layer_output[i] = sigmoid(inputs[0] * weights1[i][0] + inputs[1] * weights1[i][1] + bias1[i]);
        }
        double output = sigmoid(hidden_layer_output[0] * weights2[0] + hidden_layer_output[1] * weights2[1] + bias2);

        // Backward propagation
        double output_error = target - output;
        double output_delta = output_error * sigmoid_derivative(output);

        vector<double> hidden_error(2);
        vector<double> hidden_delta(2);
        for (int i = 0; i < 2; ++i) {
            hidden_error[i] = output_delta * weights2[i];
            hidden_delta[i] = hidden_error[i] * sigmoid_derivative(hidden_layer_output[i]);
        }

        // Update weights and biases
        for (int i = 0; i < 2; ++i) {
            weights2[i] += learning_rate * output_delta * hidden_layer_output[i];
            bias1[i] += learning_rate * hidden_delta[i];
            for (int j = 0; j < 2; ++j) {
                weights1[i][j] += learning_rate * hidden_delta[i] * inputs[j];
            }
        }
        bias2 += learning_rate * output_delta;

        return output;
    }

    double predict(vector<double> inputs) {
        vector<double> hidden_layer_output(2);
        for (int i = 0; i < 2; ++i) {
            hidden_layer_output[i] = sigmoid(inputs[0] * weights1[i][0] + inputs[1] * weights1[i][1] + bias1[i]);
        }
        return sigmoid(hidden_layer_output[0] * weights2[0] + hidden_layer_output[1] * weights2[1] + bias2);
    }
};

int main() {
    NeuralNetwork nn(0.1);
    vector<vector<double>> inputs = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<double> outputs = {0, 1, 1, 0};

    for (int epoch = 0; epoch <= 25000; ++epoch) {
        for (int i = 0; i < 4; ++i) {
            nn.train(inputs[i], outputs[i]);
        }

        if (epoch % 5000 == 0) {
            cout << "Epoch: " << epoch << endl;
            for (int i = 0; i < 4; ++i) {
                cout << "Input: " << inputs[i][0] << " " << inputs[i][1] << " Output: " << nn.predict(inputs[i]) << endl;
            }
            cout << endl;
        }
    }

    return 0;
}