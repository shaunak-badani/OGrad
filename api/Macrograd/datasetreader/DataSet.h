#ifndef DATASET_H
#define DATASET_H
#include "Node.h"
#include <iostream>
#include <memory>

class DataSet
{
    private:
        std::shared_ptr<Node> data;
        std::shared_ptr<Node> labels;
    
    public:

        std::shared_ptr<Node> getData();
        std::shared_ptr<Node> getLabels();

        DataSet(std::vector<std::vector<float>> data, std::vector<std::vector<float>> labels);
};


#endif