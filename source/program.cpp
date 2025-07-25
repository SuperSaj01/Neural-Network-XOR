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
#include <vector>

double sigmoid(double input)
{
    return 1.0 / (1.0 + exp(-input));
};

class Layer
{
private:
    
    
public:
    Layer(int numberOfNodeInputs, int nodesOutput);
    
};

Layer::Layer(int numberOfNodeInputs, int nodesOutputs) : numberOfNodeInputs(numberOfNodeInputs), nodesOutput(nodesOutput)
{
 
}

class NeuralNetwork
{
private:
    std::vector<int>  NumberOfNeuronsInEachLayer;
    std::vector<std::vector<int>> weights;
    std::vector<double> biases; 

    void SetUpInputsAndOutputsNeurons();
public:
    NeuralNetwork(const std::vector<int>& NumberOfNeuronsInEachLayer);
};

NeuralNetwork::NeuralNetwork(const std::vector<int>& NumberOfNeuronsInEachLayer) : NumberOfNeuronsInEachLayer(NumberOfNeuronsInEachLayer)
{

}

void NeuralNetwork::SetUpInputsAndOutputsNeurons()
{

}



int main()
{
    std::vector<int> neuronList = { 2, 3, 1 };
    NeuralNetwork nn(neuronList);
}


