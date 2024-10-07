#include "CSVReader.h"
#include "IOUtils.h"
#include <fstream>
#include <sstream>
#include "DataSet.h"
#include <filesystem>
#include <iostream>

CSVReader::CSVReader(std::string filePath, int batch_size)
{
    if(!std::filesystem::exists(filePath))
    {
        std::string errorMessage = "Filename " + filePath + " doesn't exist!";
        throw std::runtime_error(errorMessage);
    }
    this->filePath = filePath;
    this->batch_size = batch_size;
    this->filePos = 0;
}

std::shared_ptr<DataSet> CSVReader::readNextBatch()
{
    std::vector<std::vector<float>> csvData;
    std::vector<std::vector<float>> csvLabels;
    std::ifstream myfile;
    if(!myfile.is_open())
    {
        myfile.open(this->filePath);
    }
    std::string currentDataPoint;
    myfile.seekg(this->filePos);
    
    if(myfile.peek() == EOF)
    {
        this->filePos = 0;
        myfile.seekg(this->filePos);
    }


    if(myfile.is_open())
    {
        for(int bufferedIndex = 0 ; bufferedIndex < this->batch_size && myfile.good() ; bufferedIndex++)
        {
            
            std::getline(myfile, currentDataPoint, ',');
            csvLabels.push_back(IOUtils::to_float({ currentDataPoint }));
            std::getline(myfile, currentDataPoint, '\n');

            csvData.push_back(IOUtils::to_float(
                IOUtils::split_comma_separated_string(currentDataPoint)
            ));
        }
    }

    this->filePos = myfile.tellg();
    myfile.close();

    return std::make_shared<DataSet>(
        csvData, csvLabels
    );;
    
}