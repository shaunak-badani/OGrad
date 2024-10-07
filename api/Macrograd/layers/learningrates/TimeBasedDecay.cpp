#include "TimeBasedDecay.h"
#include <iostream>

TimeBasedDecay::TimeBasedDecay(float learningRate, float decay)
{
    this->learningRate = learningRate;
    this->decay = decay;
}


float TimeBasedDecay::getLearningRate(int stepNumber)
{
    return this->learningRate / (1 + (this->decay * stepNumber));
}