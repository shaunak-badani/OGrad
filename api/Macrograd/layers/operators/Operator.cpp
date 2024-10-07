#include "Operator.h"

void Operator::propagateGradientBackward(std::weak_ptr<Node> operand, std::weak_ptr<Node> out)
{
    std::shared_ptr<Node> operandSharedPtr = operand.lock();
    std::shared_ptr<Node> outSharedPtr = out.lock();

    if(!operandSharedPtr)
        throw std::runtime_error("Can't access operand lock");

    if(!outSharedPtr)
        throw std::runtime_error("Can't access out lock");

    std::shared_ptr<Mat> grad = gradient(operandSharedPtr, outSharedPtr);
    std::shared_ptr<Mat> gradToBeAdded = grad.get()->mapFunction([=](int i, int j, float value){
        return value * outSharedPtr->grad->at(i, j);
    });
    *(operandSharedPtr->grad) += *gradToBeAdded.get();
}

std::shared_ptr<Node> Operator::operate(std::shared_ptr<Node> a)
{
    std::shared_ptr<Node> out = std::make_shared<Node>(calculate(a->data),
        std::unordered_set<std::shared_ptr<Node>>({a}));

    // creating weak pointers in order to prevent memory leaks;
    std::weak_ptr<Node> weakA(a);
    std::weak_ptr<Node> weakOut(out);
    out->backward = [weakA, weakOut, this](){ 
        propagateGradientBackward(weakA, weakOut); 
    };
    return out;
}