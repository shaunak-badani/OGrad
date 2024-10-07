#include "LossFn.h"
#include <iostream>
#include <memory>
#include "Node.h"
#include "Operator.h"

class RootMeanSquaredError : public LossFn
{
    private:
        std::shared_ptr<Operator> squaredOperator;
        std::shared_ptr<Operator> squareRootOperator;
    public:
        RootMeanSquaredError();

        std::shared_ptr<Node> operator()(std::shared_ptr<Node> actualValues, 
                std::shared_ptr<Node> expectedValues) override;
};