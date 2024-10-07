#ifndef LOSS_FN_H
#define LOSS_FN_H

#include <iostream>
#include <memory>
#include "Node.h"


class LossFn
{
    public:
        virtual std::shared_ptr<Node> operator()(
                    std::shared_ptr<Node> actualValues, 
                    std::shared_ptr<Node> expectedValues) = 0;
};

#endif