#include <gtest/gtest.h>
#include "DataSetReader.h"
#include "CSVReader.h"
#include <iostream>
#include <memory>
#include "DataSetsPathConfig.h"

void expect_pair_eq(std::vector<int> expectedPair, std::vector<int> actualPair)
{
    EXPECT_EQ(expectedPair.at(0), actualPair.at(0));
    EXPECT_EQ(expectedPair.at(1), actualPair.at(1));
}


TEST(DataSetReader, CSVReader)
{
    std::string filePath = DATASETS_PATH + "/mnist/mnist_train.csv";
    std::shared_ptr<DataSetReader> dataSetReader = std::make_shared<CSVReader>(
        filePath,
        32
    );

    std::shared_ptr<DataSet> dataSet = dataSetReader->readNextBatch();

    std::vector<int> dataShape = dataSet->getData()->data->getShape();
    std::vector<int> labelsShape = dataSet->getLabels()->data->getShape();

    expect_pair_eq(dataShape, std::vector<int>({32, 784}));
    expect_pair_eq(labelsShape, std::vector<int>({32, 1}));
}

TEST(DataSetReader, CSVReaderNegativeTest)
{
    std::string filePath = DATASETS_PATH + "doesNotExistFileName";

    EXPECT_THROW(
        std::make_shared<CSVReader>(filePath,2),
        std::runtime_error
    );
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}