#include "Vec3D.h"


Vec3D::Vec3D(std::vector<svf> p)
{
    for(svf twodvec : p)
        this->vec.push_back(std::make_shared<Mat>(twodvec));
}

std::vector<int> Vec3D::getShape() const
{
    int m = this->vec.size();

    if(!m)
        return {0, 0, 0};
    
    std::vector<int> matShape = this->vec[0]->getShape();

    return { m, matShape.at(0), matShape.at(1) };
}

std::shared_ptr<Mat> Vec3D::getMatAt(int i)
{
    int m = this->vec.size();
    if(i >= m || i < 0)
        throw std::runtime_error("Attempting to access matrix at index " + std::to_string(i) + " of maximum size " + std::to_string(m));
    
    return this->vec.at(i);
}