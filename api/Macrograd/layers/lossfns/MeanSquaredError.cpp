#include "MeanSquaredError.h"
#include <memory>
#include <iostream>
#include "Operator.h"
#include "Pow.h"

MeanSquaredError::MeanSquaredError()
{
    this->powerOperator = std::make_shared<Pow>(2);
}


std::shared_ptr<Node> MeanSquaredError::operator()(std::shared_ptr<Node> actualValues, 
        std::shared_ptr<Node> expectedValues)
{
    return sum(this->powerOperator->operate(actualValues - expectedValues));
}
