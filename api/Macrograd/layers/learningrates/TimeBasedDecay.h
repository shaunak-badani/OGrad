#ifndef TIME_BASED_DECAY
#define TIME_BASED_DECAY
#include "LearningRate.h"

class TimeBasedDecay : public LearningRate
{
    private:
        float decay;
        float learningRate;
        
    public:
        TimeBasedDecay(float learningRate, float decay);

        float getLearningRate(int stepNumber) override;

};


#endif