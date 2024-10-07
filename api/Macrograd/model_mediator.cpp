#include "model_mediator.h"
#include "CSVReader.h"
#include "DataSetsPathConfig.h"
#include "ModelBuilder.h"
#include "Layer.h"
#include "Linear.h"
#include "LossFn.h"
#include "MeanSquaredError.h"
#include "RootMeanSquaredError.h"
#include "SoftmaxCrossEntropyLoss.h"
#include "StaticLR.h"
#include "TimeBasedDecay.h"
#include "StepDecay.h"
#include "output_handler.h"
#include <ctime>

void from_json(const nlohmann::json& j, ModelMediator& modelMediator)
{
    j.at("num_epochs").get_to(modelMediator.num_epochs);

    // getting dataset reader
    int batch_size;
    std::string dataset_reader; 
    std::string file_path;
    j.at("batch_size").get_to(batch_size);
    j.at("dataset_reader").get_to(dataset_reader);
    j.at("dataset").get_to(file_path);

    // TODO: move this to factory
    file_path = DATASETS_PATH + "/" + file_path;

    if(dataset_reader == "csv_reader")
        modelMediator.dataset_reader = std::make_shared<CSVReader>(file_path, batch_size);
    else
        throw std::runtime_error("Reader not supported!");

    std::vector<nlohmann::json> layers = j.at("layers");

    std::shared_ptr<ModelBuilder> modelBuilder = std::make_shared<ModelBuilder>();

    std::string model_out;
    j.at("output_folder").get_to(model_out);
    modelMediator.output_handler = std::make_shared<OutputHandler>(model_out);

    for(nlohmann::json json_layer : layers)
    {
        std::string layer_type;
        json_layer.at("type").get_to(layer_type);
        std::shared_ptr<Layer> layer;

        if(layer_type == "linear")
        {
            layer = std::make_shared<Linear>(json_layer["input_size"], json_layer["output_size"]);
        }
        else
            throw std::runtime_error("Layer type not supported!");
        // not adding activation function right now
        modelBuilder->addLayer(layer);
    }

    nlohmann::json lr_json = j.at("learning_rate");
    std::shared_ptr<LearningRate> lr;
    float lr_value = lr_json["value"];
    if(lr_json["type"] == "simple")
        lr = std::make_shared<StaticLR>(lr_value);
    else if(lr_json["type"] == "time_based_decay")
    {
        float decay = lr_json["decay"];
        lr = std::make_shared<TimeBasedDecay>(lr_value, decay);
    }
    else if(lr_json["type"] == "step_decay")
    {
        float drop = lr_json["drop"];
        float epochs_drop = lr_json["epochs_drop"];

        lr = std::make_shared<StepDecay>(lr_value, drop, epochs_drop);
    }
    else
        throw std::runtime_error("Learning rate not supported!");

    modelBuilder->setLearningRate(lr);

    std::shared_ptr<LossFn> lossFn;
    if(j["loss_fn"] == "mean_squared")
        lossFn = std::make_shared<MeanSquaredError>();
    else if(j["loss_fn"] == "root_mean_squared")
        lossFn = std::make_shared<RootMeanSquaredError>();
    else if(j["loss_fn"] == "softmax_with_ce")
        lossFn = std::make_shared<SoftmaxCrossEntropyLoss>();
    else
        throw std::runtime_error("Loss fn not supported!");

    modelBuilder->setLossFn(lossFn);

    modelMediator.model = modelBuilder->build();
}

void ModelMediator::run()
{
    clock_t start = clock();
    for(int i = 1 ; i <= num_epochs ; i++)
    {
        // get inputs
        std::shared_ptr<DataSet> dataSet = dataset_reader->readNextBatch();
        float loss = model->train(dataSet->getData()->data, dataSet->getLabels()->data, i);
        std::cout << "Loss for epoch " << i << ": " << loss << std::endl;
        this->output_handler->register_scalar(loss);
        this->output_handler->print_scalars(i);
        this->output_handler->flush_scalars();
    }
    clock_t end = clock();
    double total_time_taken = double(end - start) / CLOCKS_PER_SEC;
    this->output_metrics.setTimeTaken(total_time_taken);
}

void ModelMediator::summarize()
{
    // Adding output metrics to json file
    std::cout << this->getJson() << std::endl;
    this->getJson()["time_taken"] = this->output_metrics.getTimeTaken();

    this->output_handler->print_model(this->model);
    std::string fileName = "out.json";
    std::string absolutePath = this->output_handler->get_files_path() + "/" + fileName;
    std::ofstream currentFile;
    currentFile.open(absolutePath);
    currentFile << std::setw(4) << this->getJson();
    currentFile.close();
}

void ModelMediator::setJson(nlohmann::json& json)
{
    this->input = json;
}

nlohmann::json& ModelMediator::getJson()
{
    return this->input;
}