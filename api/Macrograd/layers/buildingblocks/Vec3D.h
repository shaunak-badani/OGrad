#ifndef VEC_3D_H
#define VEC_3D_H
#include "Vec.h"
#include "Mat.h"

class Vec3D : public Vec
{
    private:
        std::vector<std::shared_ptr<Mat>> vec;

    public:
        Vec3D(std::vector<svf> piece);

        std::vector<int> getShape() const override;

        std::shared_ptr<Mat> getMatAt(int i);

};

#endif