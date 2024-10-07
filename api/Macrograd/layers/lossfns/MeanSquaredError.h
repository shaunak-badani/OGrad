#include "LossFn.h"
#include <iostream>
#include <memory>
#include "Node.h"
#include "Operator.h"

class MeanSquaredError : public LossFn
{
    private:
        std::shared_ptr<Operator> powerOperator;
    public:
        MeanSquaredError();

        std::shared_ptr<Node> operator()(std::shared_ptr<Node> actualValues, 
                std::shared_ptr<Node> expectedValues) override;
};