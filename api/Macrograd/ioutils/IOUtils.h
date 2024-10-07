#ifndef IO_UTILS_H
#define IO_UTILS_H
#include <vector>
#include <iostream>

class IOUtils
{
    public:
        static std::vector<std::string> split_string(std::string stringValue, char delimiter);

        static std::vector<std::string> split_comma_separated_string(std::string stringValue);

        static std::vector<float> to_float(std::vector<std::string> stringVector);
};

#endif