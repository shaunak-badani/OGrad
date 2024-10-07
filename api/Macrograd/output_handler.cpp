#include <iostream>
#include "output_handler.h"
#include <filesystem>

OutputHandler::OutputHandler(std::string files_path)
{
    if(!std::filesystem::exists(files_path))
    {
        std::cout << files_path << " doesn't exist. Creating directory..." << std::endl;
        std::filesystem::create_directories(files_path);
    }

    this->files_path = files_path;
    this->outFile.open(this->files_path + "/scalars.csv");
}


void OutputHandler::register_scalar(float value)
{
    this->scalar_values.push_back(value);
}

void OutputHandler::print_scalars(int epoch_number)
{
    outFile << epoch_number << ",";

    int scalar_index;
    for(scalar_index = 0 ; scalar_index < scalar_values.size() - 1 ; scalar_index++)
    {
        outFile << scalar_values[scalar_index] << ",";
    }
    outFile << scalar_values[scalar_index] << std::endl;
}

void OutputHandler::flush_scalars()
{
    this->scalar_values = std::vector<float>();
}

std::string OutputHandler::get_files_path()
{
    return this->files_path;
}


/* Model printing */

void OutputHandler::print_model(std::shared_ptr<Model> model)
{
    std::vector<std::shared_ptr<Node>> layers = model->parameters();

    if(!std::filesystem::exists(files_path + "/model"))
    {
        std::filesystem::create_directories(files_path + "/model");
    }


    for(int layerIndex = 0 ; layerIndex < layers.size() ; layerIndex++)
    {
        std::string fileName = std::to_string(layerIndex) + ".csv";
        std::string absolutePath = files_path + "/model/" + fileName;
        std::ofstream currentFile;
        currentFile.open(absolutePath);
        currentFile << *layers[layerIndex]->data.get();
        currentFile.close();
    }
}

OutputHandler::~OutputHandler()
{
    this->outFile.close();
}