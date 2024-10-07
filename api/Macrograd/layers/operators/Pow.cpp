#include "Pow.h"
#include <math.h>

std::shared_ptr<Mat> Pow::calculate(std::shared_ptr<Mat> operand)
{

    return operand->mapFunction([=](int i, int j, float value) { return pow(value, this->exponent); });
}

std::shared_ptr<Mat> Pow::gradient(std::shared_ptr<Node> operand, std::shared_ptr<Node> out)
{
    return operand->data->mapFunction([=](int i, int j, float value){
        return this->exponent * pow(value, this->exponent - 1);
    });
}