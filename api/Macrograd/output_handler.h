#ifndef OUTPUT_HANDLER
#define OUTPUT_HANDLER
#include <iostream>
#include <vector>
#include <fstream>
#include "Model.h"

class OutputHandler
{
    private:
        std::vector<float> scalar_values;
        std::string files_path;
        std::ofstream outFile;

    public:
        void print_scalars(int epoch_number);
        void register_scalar(float value);
        void flush_scalars();
        void print_model(std::shared_ptr<Model> model);
        std::string get_files_path();

        OutputHandler(std::string file_path);
        ~OutputHandler();
    
};

#endif