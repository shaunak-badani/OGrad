#include "StaticLR.h"

StaticLR::StaticLR(float learningRate)
{
    this->learningRate = learningRate;
}

float StaticLR::getLearningRate(int stepNumber)
{
    return this->learningRate;
}