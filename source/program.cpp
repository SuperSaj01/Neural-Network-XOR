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

static double sigmoid(double input)
{
    return 1.0 / (1.0 + exp(-input));
};

class Layer
{
private:
    int nodesInput;
    int nodesOutput;
    std::vector<std::vector<double>> weights;
    std::vector<double> biases;
    void InitialiseWeights();
public:
    Layer(int nodeInput, int nodesOutput);
    void InitialiseWeightsAndBiases();
   
    std::vector<double> CalculateOutput(std::vector<double> Inputs);
  
};


void Layer::InitialiseWeightsAndBiases()
{
   // std::cout << "nodes going in" << nodesInput << " " << "nodes going out: " << nodesOutput << std::endl;

    biases.resize(nodesOutput, 0.0);

    weights.resize(nodesInput, std::vector<double>(nodesOutput));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0, std::sqrt(2.0 / nodesInput));

    

    for (int i = 0; i < nodesInput; i++)
    {
        for (int j = 0; j < nodesOutput; j++)
        {
            double randomNum = ((double)std::rand() / RAND_MAX);
            weights[i][j] = randomNum;
        }
    }    
    
}


std::vector<double> Layer::CalculateOutput(std::vector<double> Inputs)
{
    std::cout << "nodes going in: " << nodesInput << " " << "nodes going out: " << nodesOutput << std::endl;

   
    std::vector<double> outputs;
    double output = 0.00;
    for (int currentOutputNode = 0; currentOutputNode < nodesOutput; currentOutputNode++)
    {
        for (int currentInputNode = 0; currentInputNode < nodesInput; currentInputNode++)
        {
            std::cout << "weights: [" 
                << currentInputNode 
                << "] ["
                << currentOutputNode
                << "] "
                << weights[currentInputNode][currentOutputNode] << std::endl;
            output += weights[currentInputNode][currentOutputNode] * Inputs[0];
        }
        output += biases[currentOutputNode];
        output = sigmoid(output);
        outputs.push_back(output);
    }

    return outputs; 
    

    // std::cout << biases[1]; Something going wrong here 
}


Layer::Layer(int nodesInput, int nodesOutput) : nodesInput(nodesInput), nodesOutput(nodesOutput)
{
    InitialiseWeightsAndBiases();
}

class NeuralNetwork
{
private:
    std::vector<int>  NumberOfNeuronsInEachLayer;
    void SetUpLayers(std::vector<int> NumberOfNeuronsInEachLayer);

public:
    NeuralNetwork(const std::vector<int>& NumberOfNeuronsInEachLayer);
    std::vector<Layer> layers;
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
    std::vector<double> inputLayer = { 1, 1 };

    NeuralNetwork nn(neuronList);
   
    for (Layer layer : nn.layers)
    {
        inputLayer = layer.CalculateOutput(inputLayer);
    }

    for (double num : inputLayer)
    {
        std::cout << num;
    }
    
}


