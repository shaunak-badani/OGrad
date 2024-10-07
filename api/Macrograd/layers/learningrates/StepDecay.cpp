#include "StepDecay.h"
#include "math.h"
#include <iostream>

StepDecay::StepDecay(float learningRate, float drop, float epochs_drop)
{
    this->learningRate = learningRate;
    this->drop = drop;
    this->epochs_drop = epochs_drop;
}

float StepDecay::getLearningRate(int stepNumber)
{
    return this->learningRate * pow(drop, floor(stepNumber / this->epochs_drop));
}