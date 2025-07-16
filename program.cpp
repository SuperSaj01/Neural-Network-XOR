/*
 SUMMARY:
 Making a neural network which is trained to take 2 inputs, 1 or 0, and apply a XOR logic to the inputs to output either 1 or 0. 

 XOR table:
 A | B | O
 ---------
 0 | 0 | 0
 0 | 1 | 1
 1 | 0 | 1
 1 | 1 | 0

*/
#include <iostream>
#include <cmath>

double sigmoid(double input)
{
    return 1.0 / (1.0 + exp(-input));
};

class Layer
{
    private:
    int numberOfNodeInputs, nodesOutput;
    public:
    Layer(int numberOfNodeInputs, int nodesOutput);
    
};

Layer::Layer(int numberOfNodeInputs, int nodesOutputs)
{
    x = numberOfNodeInputs;
    y = nodesOutputs;
}

class NeuralNetwork
{

};



int main()
{
    int A = 1;
    int B = 1;

    double W11 = 1.0;
    double W12 = 1.0;
    double b1 = 0.5;

    double W21 = 1.0;
    double W22 = 1.0;
    double b2 = -1.5;

    double W31 = 1.0;
    double W32 = 1.0;
    double b3 = -1.0;

    double h1 = sigmoid((A * W11) + (B * W12) + b1);
    double h2 = sigmoid((A * W21) + (B * W22) + b2);

    double output = sigmoid((h1 * W31) + (h2 * W32) + b3);

    int finalOutput = (output <= 0.5) ? 0 : 1;

    std::cout << finalOutput;
    std::cin.get();
}
