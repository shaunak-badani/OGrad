#ifndef MODEL_MEDIATOR_H
#define MODEL_MEDIATOR_H
#include <nlohmann/json.hpp>
#include "Model.h"
#include "DataSetReader.h"
#include "output_handler.h"
#include "output_metrics.h"

class ModelMediator
{
    public:
        int num_epochs;
        std::shared_ptr<Model> model;
        std::shared_ptr<DataSetReader> dataset_reader;
        std::shared_ptr<OutputHandler> output_handler;
        OutputMetrics output_metrics;

        void run();
        void summarize();

        void setJson(nlohmann::json& json);
        nlohmann::json& getJson();
    
    private:
        nlohmann::json input;

};


void from_json(const nlohmann::json& j, ModelMediator& p);

#endif