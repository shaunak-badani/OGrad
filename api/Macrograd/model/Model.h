#ifndef MODEL_H
#define MODEL_H
#include "Node.h"
#include "Layer.h"
#include <iostream>
#include <vector>
#include <memory>
#include "LossFn.h"
#include "LearningRate.h"
#include "LayerUtils.h"

class Model
{
    private:
        std::shared_ptr<LayerUtils> layerUtils;
    public:
        std::vector<std::shared_ptr<Layer>> layers;
        std::shared_ptr<LossFn> lossFn;
        std::shared_ptr<LearningRate> lr;

        Model(
            std::vector<std::shared_ptr<Layer>> layers,
            std::shared_ptr<LossFn> lossFn,
            std::shared_ptr<LearningRate> lr);

        std::shared_ptr<Node> forward(std::shared_ptr<Node> input, std::shared_ptr<Node> traininglabels);

        // returns the loss evaluated
        float train(std::shared_ptr<Mat> input, std::shared_ptr<Mat> trainingLabels, int epochNumber);

        std::vector<std::shared_ptr<Node>> parameters();
        
};

#endif
