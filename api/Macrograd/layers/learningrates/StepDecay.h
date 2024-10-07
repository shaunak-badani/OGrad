#ifndef STEP_DECAY_H
#define STEP_DECAY_H
#include "LearningRate.h"

class StepDecay : public LearningRate
{
    private:
        float learningRate;
        float drop;
        float epochs_drop;
        
    public:
        StepDecay(float learningRate, float drop, float epochs_drop);

        float getLearningRate(int stepNumber) override;
};

#endif