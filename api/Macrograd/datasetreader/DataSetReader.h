#ifndef DATASET_READER_H
#define DATASET_READER_H

#include <iostream>
#include <vector>
#include <memory>
#include "DataSet.h"

class DataSetReader
{
    protected:
        int batch_size;

    public:

        virtual std::shared_ptr<DataSet> readNextBatch() = 0;
};

#endif