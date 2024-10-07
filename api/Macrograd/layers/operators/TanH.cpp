#include "TanH.h"
#include <math.h>
#include <iostream>
#include <memory>

std::shared_ptr<Mat> TanH::calculate(std::shared_ptr<Mat> operand)
{
    return operand->mapFunction([](int i, int j, float value) { return tanh(value); } );
}

std::shared_ptr<Mat> TanH::gradient(std::shared_ptr<Node> operand, std::shared_ptr<Node> out)
{
    return operand->data->mapFunction([](int i, int j, float value) { 
        return 1 - pow(tanh(value), 2);
    });
}