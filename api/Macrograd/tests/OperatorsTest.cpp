#include "Mat.h"
#include "TanH.h"
#include "Operator.h"
#include "Node.h"
#include <gtest/gtest.h>
#include "Pow.h"


TEST(OperatorsTest, TanH)
{
    svf p = {
        {1.0, 2.0},
        {3.0, 4.0}
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(p);
    std::shared_ptr<Node> input = std::make_shared<Node>(a);
    std::shared_ptr<Operator> tanh = std::make_shared<TanH>();
    std::shared_ptr<Node> y = tanh.get()->operate(input);

    svf expectedOutput = {
        {0.76159, 0.96402},
        {0.99505, 0.9993292}
    };

    EXPECT_EQ(y->previous.size(), 1) << "The unary operator tanh should have 1 child" << std::endl;


    y->data->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedOutput[i][j] - value) < 1e-4);
    }); 

    y->grad->assignValue(1.0);

    y->backward();

    svf expectedGrad = {
        {0.419974376, 0.070650825},
        {0.009866038, 0.00134095}
    };

    input->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedGrad[i][j] - value) < 1e-3);
    });
}

TEST(OperatorsTest, Pow)
{
    svf p = {
        {-2.0, 2.0},
        {3.0, 4.0}
    };
    int exponent = 3;

    std::shared_ptr<Mat> a = std::make_shared<Mat>(p);
    std::shared_ptr<Node> input = std::make_shared<Node>(a);
    std::shared_ptr<Operator> pow = std::make_shared<Pow>(exponent);
    std::shared_ptr<Node> y = pow.get()->operate(input);

    EXPECT_EQ(y->previous.size(), 1) << "The unary operator pow should have 1 child" << std::endl;
    
    svf expectedOutput = {
        {-8, 8},
        {27, 64}
    };

    y->data->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedOutput[i][j] - value) < 1e-4);
    }); 

    y->grad->assignValue(1.0);

    y->backward();

    svf expectedGrad = {
        {12.0, 12.0},
        {27.0, 48.0}
    };


    input->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedGrad[i][j] - value) < 1e-3);
    });
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
