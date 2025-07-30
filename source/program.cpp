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
#include <random>

double sigmoid(double input)
{
    return 1.0 / (1.0 + exp(-input));
};

class Layer
{
private:
    int nodeInput;
    int nodesOutput;
    std::vector<std::vector<double>> weights;
    std::vector<double> biases;
    void InitialiseWeights();
public:
    Layer(int nodeInput, int nodesOutput);
    void InitialiseWeightsAndBiases();
};


void Layer::InitialiseWeightsAndBiases()
{
    biases.resize(nodesOutput, 0.0);

    weights.resize(nodeInput, std::vector<double>(nodesOutput));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0, std::sqrt(2.0 / nodeInput));

    double randomNum = ((double)std::rand() / RAND_MAX);

    for (int i = 0; i < nodeInput; i++)
    {
        for (int j = 0; j < nodesOutput; j++)
        {
            weights[i][j] = randomNum;
        }
    }    
    
}

Layer::Layer(int nodeInput, int nodesOutput) : nodeInput(nodeInput), nodesOutput(nodesOutput)
{
    InitialiseWeightsAndBiases();
}

class NeuralNetwork
{
private:
    std::vector<int>  NumberOfNeuronsInEachLayer;
    std::vector<Layer> layers;
    void SetUpLayers(std::vector<int> NumberOfNeuronsInEachLayer);

public:
    NeuralNetwork(const std::vector<int>& NumberOfNeuronsInEachLayer);
};

NeuralNetwork::NeuralNetwork(const std::vector<int>& NumberOfNeuronsInEachLayer) : NumberOfNeuronsInEachLayer(NumberOfNeuronsInEachLayer)
{
    SetUpLayers(NumberOfNeuronsInEachLayer);
}

void NeuralNetwork::SetUpLayers(std::vector<int> NumberOfNeuronsInEachLayer)
{
    for (int i = 0; i < NumberOfNeuronsInEachLayer.size() - 1; i++)
    {
        layers.push_back(Layer(NumberOfNeuronsInEachLayer[i], NumberOfNeuronsInEachLayer[i + 1]));
    }
}

int main()
{
    std::vector<int> neuronList = { 2, 3, 1 };

    NeuralNetwork nn(neuronList);
   
}


