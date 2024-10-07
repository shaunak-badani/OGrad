#include "Mat.h"
#include <gtest/gtest.h>

struct NormalBehaviorSetup : public testing::Test
{
    svf a;
    svf b;

    void SetUp() override
    {
        a = {
            {1.0, -1.0, 105.0, 57.0},
            {2.1, 3.5, 9.0, 77.5},
            {1.0, -1.0, 105.0, 57.0},
            {2.1, 3.5, 9.0, 77.6},
        };

        b = {
            {9.0, 4.0, -23.2, -57.0},
            {8.2, -0.9, 2.1, 0.9},
            {4.3, -12.2, 89.9, 44.2},
            {8.9, 34.2, 41.7, -99.8}
        };
    }

    void TearDown() override
    {
    }
};

void assertClose(Mat obtainedMat, svf expectedVector)
{
    obtainedMat.forEach([=](int i, int j, float value) {
        EXPECT_TRUE(abs(value - expectedVector[i][j]) < 1e-3);
    });
}


TEST_F(NormalBehaviorSetup, Mat_addition_test)
{
    Mat A(a), B(b);
    Mat C = A + B;
    svf expectedResultVector = {
        {10.0, 3.0, 81.8, 0},
        {10.3, 2.6, 11.1, 78.4},
        {5.3, -13.2, 194.9, 101.2},
        {11.0, 37.7, 50.7, -22.2}
    };

    assertClose(C, expectedResultVector);
}

TEST_F(NormalBehaviorSetup, Mat_subtraction_test)
{
    Mat A(a), B(b);
    Mat C = A - B;

    svf expectedResultVector = {
        {-8.0, -5.0, 128.2, 114.0},
        {-6.1, 4.4, 6.9, 76.6},
        {-3.3, 11.2, 15.1, 12.8},
        {-6.8, -30.7, -32.7, 177.4}
    };
    assertClose(C, expectedResultVector);
}

TEST_F(NormalBehaviorSetup, Mat_multiplication_test)
{
    Mat A(a), B(b);
    Mat C = A * B;
    svf expectedResultVector = {
        {959.6,	673.3,	11791.1, -1105.5},
	    {776.05, 2545.95,	3999.48, -7453.25},
	    {959.6,	673.3,	11791.1, -1105.5},
	    {776.94, 2549.37, 4003.65, -7463.23}
    };  

    assertClose(C, expectedResultVector);
}

TEST_F(NormalBehaviorSetup, Mat_plus_equal_to_test)
{
    Mat A(a), B(b);
    A += B;
    
    svf expectedResultVector = {
        {10.0, 3.0, 81.8, 0},
        {10.3, 2.6, 11.1, 78.4},
        {5.3, -13.2, 194.9, 101.2},
        {11.0, 37.7, 50.7, -22.2}
    };
 

    assertClose(A, expectedResultVector);
}

TEST_F(NormalBehaviorSetup, Mat_transpose_test)
{
    Mat A(a);
    Mat C = A.T();

    std::vector<int> cShape = C.getShape();
    std::vector<int> aShape = A.getShape();
    
    EXPECT_EQ(cShape.at(0), aShape.at(1));
    EXPECT_EQ(cShape.at(1), aShape.at(0));

    C.forEach([=](int i, int j, float value){
        EXPECT_EQ(value, a[j][i]);
    });

}

TEST_F(NormalBehaviorSetup, Minus_Equal_and_Multiplication)
{
    std::shared_ptr<Mat> matA = std::make_shared<Mat>(a);
    std::shared_ptr<Mat> matB = std::make_shared<Mat>(b);
    matA -= matB;
    
    svf expectedResultVector = {
        {-8.0, -5.0, 128.2, 114.0},
        {-6.1, 4.4, 6.9, 76.6},
        {-3.3, 11.2, 15.1, 12.8},
        {-6.8, -30.7, -32.7, 177.4}
    };
    matA->forEach([=](int i, int j, float value) {
        EXPECT_FLOAT_EQ(expectedResultVector[i][j], value);
    });

    matA = std::make_shared<Mat>(a);
    std::shared_ptr<Mat> matC = 0.4 * matA;

    matC->forEach([=](int i, int j, float value) {
        EXPECT_FLOAT_EQ(value, 0.4 * a[i][j]);
    });
}

struct ErrorThrowSetup : public testing::Test
{
    svf a;
    svf b;

    void SetUp() override
    {
        a = {
            {1.0, -1.0, 105.0, 57.0},
            {2.1, 3.5, 9.0, 77.5},
        };

        b = {
            {9.0},
            {8.2},
            {4.3}
        };

    }

    void TearDown() override
    {
    }
};

TEST_F(ErrorThrowSetup, ThrowsErrorInBothOperations)
{
    Mat A(a);
    Mat B(b);

    EXPECT_THROW(A + B, std::runtime_error);
    EXPECT_THROW(A - B, std::runtime_error);
    EXPECT_THROW(A * B, std::runtime_error);
}

struct PartialBehaviorSetup : public testing::Test
{
    svf a;
    svf b;

    void SetUp() override
    {
        a = {
            {1.0, -1.0, 105.0, 57.0},
            {2.1, 3.5, 9.0, 77.5},
        };

        b = {
            {9.0, 4.0, 5.4},
            {8.2, -0.9, -76.2},
            {4.3, -12.2, -35.2},
            {-11.3, 20.2, 27.2}
        };

    }

    void TearDown() override
    {
    }
};

TEST_F(PartialBehaviorSetup, ThrowsErrorOnlyForAddition)
{
    Mat A(a);
    Mat B(b);

    EXPECT_THROW(A + B, std::runtime_error);
    EXPECT_THROW(A - B, std::runtime_error);

    svf expectedResultVector = {
        {-191.8, -124.7, -2064},
    	{-789.45, 1460.95, 1535.84}  
    };

    Mat C = A * B;
    assertClose(C, expectedResultVector);
}



int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}