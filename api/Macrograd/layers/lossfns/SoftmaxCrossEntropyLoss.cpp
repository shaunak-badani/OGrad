#include "SoftmaxCrossEntropyLoss.h"
#include <limits>
#include <math.h>

std::shared_ptr<Node> SoftmaxCrossEntropyLoss::operator()(std::shared_ptr<Node> actualValues, std::shared_ptr<Node> expectedValues)
{
    std::shared_ptr<Mat> P = getPValues(actualValues);
    float loss_value = 0;

    actualValues->data->forEach([&loss_value, expectedValues, P](int i, int j, float value){
        loss_value += expectedValues->data->at(i,j) * log(P->at(i,j));
    });

    int n = actualValues->data->getShape().at(0);
    loss_value *= (-1 / (float)n);

    // svf l = {{loss_value}};
    std::shared_ptr<Node> out = std::make_shared<Node>(
        std::make_shared<Mat>(svf({{loss_value}})),
        std::unordered_set<std::shared_ptr<Node>>({actualValues})
    );

    out->backward = getBackward(out, actualValues, expectedValues);

    return out;
}

std::function<void(void)> SoftmaxCrossEntropyLoss::getBackward(std::shared_ptr<Node> out, 
                std::shared_ptr<Node> actualValues, 
                std::shared_ptr<Node> expectedValues)
{

    std::weak_ptr<Node> nExpectedValues(expectedValues);
    std::weak_ptr<Node> nActualValues(actualValues);
    std::weak_ptr<Node> nOut(out);


    return [nExpectedValues, nActualValues, nOut, this]() {
            
        std::shared_ptr<Node> expectedValuesPtr = nExpectedValues.lock();
        if(!expectedValuesPtr)
            throw std::runtime_error("Failed to obtain expectedValuesPtr lock!");
        
        std::shared_ptr<Node> actualValuesPtr = nActualValues.lock();
        if(!actualValuesPtr)
            throw std::runtime_error("Failed to obtain actualValuesPtr lock!");

        std::shared_ptr<Node> outPtr = nOut.lock();
        if(!outPtr)
            throw std::runtime_error("Failed to obtain outPtr lock!");

        
        std::shared_ptr<Mat> nP(getPValues(actualValuesPtr));

        int n = expectedValuesPtr->data->getShape().at(0);

        nP->forEach([&](int i, int j, float value){
            float gradToBeAdded = outPtr->grad->at(0, 0) * (1 / (float)n) * (value - expectedValuesPtr->data->at(i, j));
            actualValuesPtr->grad->setAt(i, j, gradToBeAdded);
        });
    };
}

std::shared_ptr<Mat> SoftmaxCrossEntropyLoss::getPValues(std::shared_ptr<Node> actualValues)
{
    float m_max = std::numeric_limits<float>::min();
    actualValues->data->forEach([&m_max](int i, int j, float value){
        m_max = std::max(m_max, value);
    });
    float eps = 1e-48;

    // if max < 0, we should not be subtracting max from each data vector for exp
    // we don't subtract anything
    if(m_max < 0)
        m_max = 0;

    int n = actualValues->data->getShape().at(0);
    
    std::vector<float> sums = std::vector<float>(n, 0);
    actualValues->data->forEach([&sums, m_max](int i, int j, float value){
        sums[i] += exp(value - m_max);
    });

    return actualValues->data->mapFunction([=](int i, int j, float value){
        return (exp(value - m_max) + eps) / sums[i];
    });
}
