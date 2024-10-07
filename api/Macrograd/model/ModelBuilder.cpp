#include "ModelBuilder.h"

ModelBuilder& ModelBuilder::addLayer(std::shared_ptr<Layer> layer)
{
    this->layers.push_back(layer);
    return *this;
}

ModelBuilder& ModelBuilder::setLossFn(std::shared_ptr<LossFn> lossFn)
{
    this->lossFn = lossFn;
    return *this;
}

ModelBuilder& ModelBuilder::setLearningRate(std::shared_ptr<LearningRate> lr)
{
    this->learningRate = lr;
    return *this;
}

std::shared_ptr<Model> ModelBuilder::build()
{
    return std::make_shared<Model>(layers, lossFn, learningRate);
}