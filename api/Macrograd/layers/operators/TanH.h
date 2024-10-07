#ifndef TAN_H
#define TAN_H
#include "Operator.h"
#include "Mat.h"


class TanH : public Operator
{
    std::shared_ptr<Mat> calculate(std::shared_ptr<Mat> operand) override;

    std::shared_ptr<Mat> gradient(std::shared_ptr<Node> operand, std::shared_ptr<Node> out) override;
};

#endif