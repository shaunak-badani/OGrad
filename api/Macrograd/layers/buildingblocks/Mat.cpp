#include "Mat.h"
#include <functional>
#include <iostream>
#include <memory>

std::vector<int> Mat::getShape() const
{
    int m = this->piece.size();
    if(!m)
    {
        return {0, 0};
    }
    int n = this->piece[0].size();
    return {m, n};
}

Mat::Mat(svf p) : piece(p) 
{

}

float Mat::at(int i, int j)
{
    std::vector<int> shape = this->getShape();

    if(i >= shape.at(0))
        throw std::runtime_error("Illegal access of row index : " + std::to_string(i) 
                            + " with a row length of : " + std::to_string(shape.at(0)));
    if(j >= shape.at(1))
        throw std::runtime_error("Illegal access of column index : " + std::to_string(j) 
                            + " with a column length of : " + std::to_string(shape.at(1)));

    return this->piece[i][j];
}

void Mat::setAt(int i, int j, float value)
{
    std::vector<int> shape = this->getShape();

    if(i >= shape.at(0))
        throw std::runtime_error("Illegal access of row index : " + std::to_string(i) 
                            + " with a row length of : " + std::to_string(shape.at(0)));
    if(j >= shape.at(1))
        throw std::runtime_error("Illegal access of column index : " + std::to_string(j) 
                            + " with a column length of : " + std::to_string(shape.at(1)));

    this->piece[i][j] = value;
}

std::shared_ptr<Mat> Mat::mapFunction(std::function<float(int, int, float)> apply) const
{
    std::vector<int> shape = this->getShape();
    int noOfRows = shape.at(0);
    int noOfColumns = shape.at(1);

    svf p = svf(noOfRows, std::vector<float>(noOfColumns, 0));

    for(int i = 0 ; i < noOfRows ; i++)
    {
        for(int j = 0 ; j < noOfColumns ; j++)
        {
            p[i][j] = apply(i, j, this->piece[i][j]);
        }
    }
    return std::make_shared<Mat>(p);
}

void Mat::forEach(std::function<void(int, int, float)> apply) const
{
    std::vector<int> shape = this->getShape();
    int noOfRows = shape.at(0);
    int noOfColumns = shape.at(1);

    svf p = svf(noOfRows, std::vector<float>(noOfColumns, 0));

    for(int i = 0 ; i < noOfRows ; i++)
    {
        for(int j = 0 ; j < noOfColumns ; j++)
        {
            apply(i, j, this->piece[i][j]);
        }
    }
}

void Mat::assignValue(float value)
{
    std::vector<int> shape = this->getShape();
    int noOfRows = shape.at(0);
    int noOfColumns = shape.at(1);


    for(int i = 0 ; i < noOfRows ; i++)
    {
        for(int j = 0 ; j < noOfColumns ; j++)
        {
            this->piece[i][j] = value;
        }
    }
}

Mat Mat::operator+(Mat const& b) const
{
    if(this->getShape() != b.getShape())
    {
        throw std::runtime_error("Matrices are not of equal size!");
    }

    return *mapFunction([=](int i, int j, float value) { return b.piece[i][j] + value; }).get();
}

Mat Mat::operator-(Mat const& b) const
{
    if(this->getShape() != b.getShape())
    {
        throw std::runtime_error("Matrices are not of equal size!");
    }

    return *mapFunction([=](int i, int j, float value) { return value - b.piece[i][j]; }).get();
}

Mat Mat::operator*(Mat const& b) const
{
    std::vector<int> aShape = this->getShape();
    std::vector<int> bShape = b.getShape();

    if(aShape.at(1) != bShape.at(0))
    {
        throw std::runtime_error("Matrices cannot be multiplied!");
    }
    svf outputVector = svf(aShape.at(0), std::vector<float>(bShape.at(1), 0));
    Mat output(outputVector);

    return *output.mapFunction([=](int i, int j, float value)
    {
        float tmp = 0;
        for(int k = 0 ; k < aShape.at(1) ; k++)
        {
            tmp += this->piece[i][k] * b.piece[k][j];
        }
        return tmp;
    }).get();
}

void Mat::operator+=(Mat const& b) 
{
    this->forEach([=](int i, int j, float value)
    {
        this->piece[i][j] += b.piece[i][j];
    });
}

void Mat::operator+=(float &adder) 
{
    this->forEach([=](int i, int j, float value)
    {
        this->piece[i][j] += adder;
    });
}

std::ostream& operator<<(std::ostream& os, const Mat& a)
{
    svf vec = a.piece;
    std::vector<int> shape = a.getShape();
    for(int i = 0 ; i < shape.at(0) ; i++)
    {
        int j;
        for(j = 0 ; j < shape.at(1) - 1 ; j++)
        {
            os << a.piece[i][j] << ",";
        }
        os << a.piece[i][j];
        if(i != (shape.at(0) - 1))
            os << std::endl;
    }
    return os;
}


Mat Mat::T()
{
    std::vector<int> shape = this->getShape();
    int noOfRows = shape.at(0);
    int noOfColumns = shape.at(1);
    
    svf p = svf(noOfColumns, std::vector<float>(noOfRows, 0));
    for(int i = 0 ; i < noOfRows ; i++)
    {
        for(int j = 0 ; j < noOfColumns ; j++)
        {
            p[j][i] = this->piece[i][j];
        }
    }
    return Mat(p);
}

void operator-=(std::shared_ptr<Mat> operand, std::shared_ptr<Mat> input)
{
    operand->forEach([=](int i, int j, float value){
        operand->piece[i][j] -= input->piece[i][j];
    });
}

std::shared_ptr<Mat> operator*(float value, std::shared_ptr<Mat> input)
{
    return input->mapFunction([=](int i, int j, float p){
        return p * value;
    });
}

std::shared_ptr<Mat> operator/(std::shared_ptr<Mat> input, float value)
{
    return input->mapFunction([=](int i, int j, float p){
        return p / value;
    });
}