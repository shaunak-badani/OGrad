#ifndef LEARNING_RATE_H
#define LEARNING_RATE_H

class LearningRate
{
    public:
        virtual float getLearningRate(int stepNumber) = 0;
};

#endif