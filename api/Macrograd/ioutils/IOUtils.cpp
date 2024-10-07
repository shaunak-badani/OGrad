#include "IOUtils.h"
#include <vector>
#include <iostream>

std::vector<std::string> IOUtils::split_string(std::string stringValue, char delimiter)
{
    size_t pos_start = 0;
    size_t delim_len = 1;
    size_t pos_end;
    std::string token;
    std::vector<std::string> splitValues;
    while((pos_end = stringValue.find(delimiter, pos_start)) != std::string::npos) 
    {
        token = stringValue.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        splitValues.push_back(token);
    }
    splitValues.push_back(stringValue.substr(pos_start));
    return splitValues;
}

std::vector<std::string> IOUtils::split_comma_separated_string(std::string stringValue)
{
    return split_string(stringValue, ',');
}

std::vector<float> IOUtils::to_float(std::vector<std::string> stringVector)
{
    int vectorSize = stringVector.size();
    std::vector<float> floatVector = std::vector<float>(vectorSize, 0);

    for(int i = 0 ; i < vectorSize ; i++)
    {
        floatVector[i] = std::stof(stringVector[i]);
    }
    
    return floatVector;
}
