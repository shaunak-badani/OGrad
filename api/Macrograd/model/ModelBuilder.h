#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H
#include "Model.h"
#include "LossFn.h"
#include "LearningRate.h"

class ModelBuilder
{
    private:
        std::vector<std::shared_ptr<Layer>> layers;

        std::shared_ptr<LossFn> lossFn;

        std::shared_ptr<LearningRate> learningRate;

    public:
        ModelBuilder& addLayer(std::shared_ptr<Layer> layer);

        ModelBuilder& setLossFn(std::shared_ptr<LossFn> lossFn);

        ModelBuilder& setLearningRate(std::shared_ptr<LearningRate> lr);

        std::shared_ptr<Model> build();
};

#endif