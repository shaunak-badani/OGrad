#include "DataSet.h"
#include "Mat.h"
#include "Node.h"

DataSet::DataSet(std::vector<std::vector<float>> data, std::vector<std::vector<float>> labels)
{
    this->data = std::make_shared<Node>(
        std::make_shared<Mat>(data)
    );
    this->labels = std::make_shared<Node>(
        std::make_shared<Mat>(labels)
    );
}

std::shared_ptr<Node> DataSet::getData()
{
    return this->data;
}

std::shared_ptr<Node> DataSet::getLabels()
{
    return this->labels;
}