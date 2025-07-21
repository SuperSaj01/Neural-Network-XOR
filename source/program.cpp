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
    numberOfNodeInputs = numberOfNodeInputs;
    nodesOutput = nodesOutputs;
}

class NeuralNetwork
{

};



int main()
{
    
    
}


