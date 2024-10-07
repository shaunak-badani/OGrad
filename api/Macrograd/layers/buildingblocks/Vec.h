#ifndef VEC_H
#define VEC_H
#include <iostream>
#include <vector>

class Vec
{
    public:
        virtual std::vector<int> getShape() const = 0;
};

#endif