#include "RootMeanSquaredError.h"
#include <memory>
#include <iostream>
#include "Operator.h"
#include "Pow.h"

RootMeanSquaredError::RootMeanSquaredError()
{
    this->squaredOperator = std::make_shared<Pow>(2);
    this->squareRootOperator = std::make_shared<Pow>(0.5);
}


std::shared_ptr<Node> RootMeanSquaredError::operator()(std::shared_ptr<Node> actualValues, 
        std::shared_ptr<Node> expectedValues)
{
    int numberOfDataPoints = actualValues->data->getShape().at(0);

    return this->squareRootOperator->operate(
        sum(this->squaredOperator->operate(actualValues - expectedValues) / numberOfDataPoints)
    );
}
