#include "LearningRate.h"

class StaticLR : public LearningRate
{
    private:
        float learningRate;
    public:
    
        StaticLR(float learningRate);

        float getLearningRate(int stepNumber) override;
};
