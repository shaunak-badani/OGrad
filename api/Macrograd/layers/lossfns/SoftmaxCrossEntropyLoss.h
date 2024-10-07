#ifndef SOFTMAX_LOSS_H
#define SOFTMAX_LOSS_H
#include "LossFn.h"
#include "Node.h"

class SoftmaxCrossEntropyLoss : public LossFn
{
    private:
        std::function<void(void)> getBackward(std::shared_ptr<Node> out, 
                std::shared_ptr<Node> actualValues, 
                std::shared_ptr<Node> expectedValues);

        std::shared_ptr<Mat> getPValues(std::shared_ptr<Node> actualValues);

    public:
        // expectedValues -> (N, C) matrix with binaries. actualValues[i][j] = 1 means the ith data point belongs to the jth class
        // actualValues -> (N, C) matrix is the output of the neural network. These would be considered as logit inputs to the loss function
        std::shared_ptr<Node> operator()(std::shared_ptr<Node> actualValues, 
                std::shared_ptr<Node> expectedValues) override;
};

#endif