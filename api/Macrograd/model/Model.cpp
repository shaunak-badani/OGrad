#include "Model.h"

Model::Model(
    std::vector<std::shared_ptr<Layer>> layers, 
    std::shared_ptr<LossFn> lossFn,
    std::shared_ptr<LearningRate> lr
    )
{
    for(std::shared_ptr<Layer> layer : layers)
    {
        if(!layer)
            throw std::runtime_error("Can't initialize a model with a null layer!");
    }
    this->layers = layers;
    if(!lossFn)
        throw std::runtime_error("Can't initialize a model without a loss function!");

    this->lossFn = lossFn;
    if(!lr)
        throw std::runtime_error("Can't initialize a model without a proper learning rate!");

    this->lr = lr;
    this->layerUtils = std::make_shared<LayerUtils>();
}

std::shared_ptr<Node> Model::forward(std::shared_ptr<Node> input, std::shared_ptr<Node> traininglabels)
{
    std::shared_ptr<Node> x = input;
    for(std::shared_ptr<Layer> layer : layers)
    {
        x = layer->forward(x);
    }
    std::vector<int> outputShape = x->data->getShape();
    std::vector<int> labelsShape = traininglabels->data->getShape();
    if(outputShape.at(1) != labelsShape.at(1))
    {
        throw std::runtime_error("Label dimension doesn't match layer output dimension!");
    }
    if(outputShape.at(0) != labelsShape.at(0))
    {
        throw std::runtime_error("Number of elements in input and labels does not match!");
    }
    std::shared_ptr<Node> loss = (this->lossFn.get())->operator()(x, traininglabels);
    return loss;
}

std::vector<std::shared_ptr<Node>> Model::parameters()
{
    std::vector<std::shared_ptr<Node>> params;
    for(std::shared_ptr<Layer> layer : this->layers)
    {
        std::vector<std::shared_ptr<Node>> layerParams = layer->getParameters();
        params.insert(params.end(), layerParams.begin(), layerParams.end());
    }
    return params;
}


float Model::train(std::shared_ptr<Mat> input, std::shared_ptr<Mat> trainingLabels, int epochNumber)
{
    std::shared_ptr<Node> inputNode = std::make_shared<Node>(input);
    std::shared_ptr<Node> labelsNode = std::make_shared<Node>(trainingLabels);

    std::shared_ptr<Node> loss = this->forward(inputNode, labelsNode);
    float loss_value = loss->data->at(0, 0);
    this->layerUtils->backward(loss);

    std::vector<std::shared_ptr<Node>> modelParams = this->parameters();

    float learningRate = this->lr->getLearningRate(epochNumber);
    
    for(std::shared_ptr<Node> param : modelParams)
    {
        param->data -= learningRate * param->grad;
        param->grad->assignValue(0.0);
    }
    return loss_value;
}

