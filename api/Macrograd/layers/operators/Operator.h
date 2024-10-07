#ifndef OPERATOR_H
#define OPERATOR_H
#include <iostream>
#include <vector>
#include <functional>
#include "Node.h"
#include "Mat.h"
#include <unordered_set>
#include <algorithm>
#include <memory>

class Operator
{
    public: 
        virtual std::shared_ptr<Mat> calculate(std::shared_ptr<Mat> operand) = 0;

        virtual std::shared_ptr<Mat> gradient(std::shared_ptr<Node> operand, std::shared_ptr<Node> out) = 0;

        // a function that propagates the gradient to 
        void propagateGradientBackward(std::weak_ptr<Node> operand, std::weak_ptr<Node> out);

        std::shared_ptr<Node> operate(std::shared_ptr<Node> a);
};

#endif