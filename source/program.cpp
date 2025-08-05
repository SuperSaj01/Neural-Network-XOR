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

#include "Data.h"

const float LEARN_RATE = 0.075f;

static double ActivationFunction(double input)
{
    return 1.0 / (1.0 + exp(-input));
};

static double ComputeActivationDerivativeWrtInput(double input)
{
    double a = ActivationFunction(input);
    return (a * (1 - a));
};

static double ComputeCost(double calculatedOutput, double expectedOutput)
{
    double cost = calculatedOutput - expectedOutput;
    return pow(cost, 2);
};

static double ComputeCostDerivateWrtCalculatedOutput(double calculatedOutput, double expectedOutput)
{
    return 2 * (calculatedOutput - expectedOutput);
};

void OutputSpecificValue(std::vector<double>* inputLayer)
{
    for (double num : *inputLayer)
    {
        std::cout << num << '\n';
    }
}

void OuputAnswer(std::vector<double>* inputLayer)
{
    for (double num : *inputLayer)
    {
        std::cout << (int)num << '\n';
    }
}


class Layer
{
private:
    int nodesInput;
    int nodesOutput;

    std::vector<double> activatedInputs;
    std::vector<double> weightedInputs;


    std::vector<std::vector<double>> changeInWeightValues;
    std::vector<double> changeInBiasValues;

    void InitialiseWeights();
public:


    std::vector<double> activatedOutputs;


    Layer(int nodeInput, int nodesOutput);

    std::vector<std::vector<double>> weights;
    std::vector<double> biases;

    void InitialiseWeightsAndBiases();

    std::vector<double> CalculatePartialDerivatives(int expectedOutcome);
    std::vector<double> CalculatePartialDerivatives(std::vector<double>& PreviousPartialDerivateValues, Layer& previousLayer3);
    
    void CalculateChangeInGradientValues(std::vector<double> currentPartialDerivativeValues);

    std::vector<double> CalculateOutput(std::vector<double> Inputs);

    void UpdateWeightsAndBiases();
  
};

void Layer::UpdateWeightsAndBiases()
{
    for (int i = 0; i < nodesInput; i++)
    {
        for (int j = 0; j < nodesOutput; j++)
        {
            weights[i][j] -= changeInWeightValues[i][j] * LEARN_RATE;
            biases[j] -= changeInBiasValues[j] * LEARN_RATE;
        };
    };
}

void Layer::InitialiseWeightsAndBiases()
{
   // std::cout << "nodes going in" << nodesInput << " " << "nodes going out: " << nodesOutput << std::endl;

    biases.resize(nodesOutput, 0.0);
    changeInBiasValues.resize(nodesOutput, 0.0);

    weights.resize(nodesInput, std::vector<double>(nodesOutput));
    changeInWeightValues.resize(nodesInput, std::vector<double>(nodesOutput, 0.00));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0, std::sqrt(2.0 / nodesInput));


    for (int i = 0; i < nodesInput; i++)
    {
        for (int j = 0; j < nodesOutput; j++)
        {
            weights[i][j] = dist(gen);
        }
    }    
    
}



std::vector<double> Layer::CalculateOutput(std::vector<double> Inputs)
{
    //std::cout << "nodes going in: " << nodesInput << " " << "nodes going out: " << nodesOutput << std::endl;
    activatedInputs.clear();
    weightedInputs.clear();
    activatedOutputs.clear();

    activatedInputs = Inputs; //previous 'a'
    
   

    for (int currentOutputNode = 0; currentOutputNode < nodesOutput; currentOutputNode++)
    {

        double output = 0.00;
        for (int currentInputNode = 0; currentInputNode < nodesInput; currentInputNode++)
        {
         /*   std::cout << "weights: ["
                << currentInputNode 
                << "] ["
                << currentOutputNode
                << "] "
                << weights[currentInputNode][currentOutputNode] << std::endl; */
            output += weights[currentInputNode][currentOutputNode] * Inputs[currentInputNode];
        }
        output += biases[currentOutputNode];
        weightedInputs.push_back(output); //current 'i'
        output = ActivationFunction(output); //current 'a'
        activatedOutputs.push_back(output);
    }

    return activatedOutputs;
    

    // std::cout << biases[1]; Something going wrong here 
}

void Layer::CalculateChangeInGradientValues(std::vector<double> currentPartialDerivativeValues)
{
    for (int outputNode = 0; outputNode < nodesOutput; outputNode++)
    {
        for (int inputNode = 0; inputNode < nodesInput; inputNode++)
        {
            double costDerivativeWrtWeight = currentPartialDerivativeValues[outputNode] * activatedInputs[inputNode];
            changeInWeightValues[inputNode][outputNode] += costDerivativeWrtWeight;
        }

        changeInBiasValues[outputNode] += currentPartialDerivativeValues[outputNode];  // 1 * x is just x
    }
}

std::vector<double> Layer::CalculatePartialDerivatives(int expectedOutcome)
{

    std::vector<double> newPartialDerivativeValues(nodesOutput);

    for (int currentNode = 0; currentNode < nodesOutput; currentNode++)
    {
        double errorDerivative = ComputeCostDerivateWrtCalculatedOutput(activatedOutputs[currentNode], expectedOutcome); //Needs to change to actual expected outcome!!!!
        double activationDerivative = ComputeActivationDerivativeWrtInput(weightedInputs[currentNode]);
        double currentNodePartialDerivativeValue = errorDerivative * activationDerivative;
        newPartialDerivativeValues[currentNode] = currentNodePartialDerivativeValue;
    };

    return newPartialDerivativeValues;
}

std::vector<double> Layer::CalculatePartialDerivatives(std::vector<double>& previousPartialDerivateValues, Layer& previousBackpropLayer)
{
    std::vector<double> newPartialDerivativeValues(nodesOutput);

    for (int currentNode = 0; currentNode < nodesOutput; currentNode++)
    {
        double currentNodePartialDerivative = 0;
        for (int previousBackpropLayerNode = 0; previousBackpropLayerNode < previousPartialDerivateValues.size(); previousBackpropLayerNode++)
        {
            //This is also equal to the partial derivative of the weighted input wrt the activated output
            // dI(2) / da(1)
            double prevWeights = previousBackpropLayer.weights[currentNode][previousBackpropLayerNode];
            currentNodePartialDerivative += prevWeights * previousPartialDerivateValues[previousBackpropLayerNode];
        };
        currentNodePartialDerivative *= ComputeActivationDerivativeWrtInput(weightedInputs[currentNode]);
        newPartialDerivativeValues[currentNode] = currentNodePartialDerivative;
    };

    return newPartialDerivativeValues;
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
    void FeedForward(std::vector<double>& inputLayer);
    void BackPropagation(int expectedOutcome);

public:
    NeuralNetwork(const std::vector<int>& NumberOfNeuronsInEachLayer);
    void Learn(std::vector<Data>& traningSet);
    void Test(std::vector<Data>& unseenSet);

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


void NeuralNetwork::BackPropagation(int expectedOutcome)
{
    std::vector<double> partialDerivativeValue(0);


    partialDerivativeValue = layers[layers.size() - 1].CalculatePartialDerivatives(expectedOutcome);
    layers[layers.size() - 1].CalculateChangeInGradientValues(partialDerivativeValue);


    for (int i = layers.size() - 2; i >= 0; i--)
    {
        partialDerivativeValue = layers[i].CalculatePartialDerivatives(partialDerivativeValue, layers[i + 1]);
        layers[i].CalculateChangeInGradientValues(partialDerivativeValue);
    }
}

void NeuralNetwork::FeedForward(std::vector<double>& inputLayer)
{
    for (Layer& layer : layers)
    {
        inputLayer = layer.CalculateOutput(inputLayer);   
    }
}

void NeuralNetwork::Learn(std::vector<Data>& trainingSet)
{
    for (Data data : trainingSet)
    {
        std::vector<double> inputLayer = data.inputs;
        double expectedOutcome = data.expectedOutcome;
        FeedForward(inputLayer);
        BackPropagation(expectedOutcome);
        for (Layer& layer : layers)
        {
            layer.UpdateWeightsAndBiases();
        };
        OutputSpecificValue(&inputLayer);
    }
    
}

void NeuralNetwork::Test(std::vector<Data>& unseenSet)
{
    for (Data data : unseenSet)
    {
        std::vector<double> inputLayer = data.inputs;
        FeedForward(inputLayer);
        OuputAnswer(&inputLayer);
    }
}




int main()
{
    std::vector<int> neuronList = { 2, 3, 1};

    NeuralNetwork nn(neuronList);

    std::vector<Data> trainingSet =
    {
        Data({0,0}, {0}),
        Data({0, 1}, {1}),
        Data({1, 0}, {1}),
        Data({1, 1}, {0})
    };

    std::vector<Data> unseenSet =
    {
        Data({1,1}, {1})
    };
  
    
    for (int i = 0; i < 1000; i++)
    {
        nn.Learn(trainingSet);
    }

    std::cout << "TEST TIME: ";
    nn.Test(unseenSet);



   
}


