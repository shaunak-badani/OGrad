#ifndef LINEAR_H
#define LINEAR_H
#include "Node.h"
#include <iostream>
#include <memory>
#include "Layer.h"

class Linear : public Layer
{
    public:

        std::shared_ptr<Node> weights;

        std::shared_ptr<Node> biases;

        Linear(int input_size, int output_size);

        std::shared_ptr<Node> forward(std::shared_ptr<Node> input) override;

        std::vector<std::shared_ptr<Node>> getParameters() override;
};

#endif