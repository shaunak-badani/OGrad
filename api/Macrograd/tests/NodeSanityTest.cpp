#include "Node.h"
#include <gtest/gtest.h>
#include <memory>
#include <iostream>

TEST(NodeSetup, testing_node_sanity)
{
    svf tmpVector = {
        {1.0, -9.0},
        {9.8, 2.1}
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(tmpVector);
    std::shared_ptr<Node> node = std::make_shared<Node>(a);
    std::vector<int> gradShape = node->grad->getShape();
    EXPECT_EQ(gradShape.at(0), 2);
    EXPECT_EQ(gradShape.at(1), 2);
    node->grad->forEach([](int i, int j, float val){
        EXPECT_EQ(val, 0.0);
    });
}

TEST(NodeOperations, node_addition)
{
    svf vectorA = {
        {1.0, -9.0},
        {9.8, 2.1}
    };

    svf vectorB = {
        {2.0, -9.0},
        {8.1, 3.2}  
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(vectorA);
    std::shared_ptr<Node> nodeA = std::make_shared<Node>(a);

    std::shared_ptr<Mat> b = std::make_shared<Mat>(vectorB);
    std::shared_ptr<Node> nodeB = std::make_shared<Node>(b);

    std::shared_ptr<Node> c = nodeA + nodeB;

    EXPECT_EQ(c->previous.size(), 2) << "The addition operator should have two children, one for each operand" << std::endl;

    float randomGradientValue = 57.0;
    c->grad->assignValue(randomGradientValue);

    c->backward();

    nodeB->grad->forEach([=](int i, int j, float value){
        EXPECT_EQ(value, randomGradientValue);
    });

    nodeA->grad->forEach([=](int i, int j, float value){
        EXPECT_EQ(value, randomGradientValue);
    });
}

TEST(NodeOperations, node_subtraction)
{
    svf vectorA = {
        {1.0, -9.0},
        {9.8, 2.1}
    };

    svf vectorB = {
        {2.0, -9.0},
        {8.1, 3.2}  
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(vectorA);
    std::shared_ptr<Node> nodeA = std::make_shared<Node>(a);

    std::shared_ptr<Mat> b = std::make_shared<Mat>(vectorB);
    std::shared_ptr<Node> nodeB = std::make_shared<Node>(b);

    std::shared_ptr<Node> c = nodeA - nodeB;

    EXPECT_EQ(c->previous.size(), 2) << "The subtraction operator should have two children, one for each operand" << std::endl;

    svf expectedSubtractedVector = {
        {-1.0, 0.0},
        {1.7, -1.1}  
    };

    c->data->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedSubtractedVector[i][j] - value) < 1e-3);
    });

    float randomGradientValue = 57.0;
    c->grad->assignValue(randomGradientValue);

    c->backward();

    nodeB->grad->forEach([=](int i, int j, float value){
        EXPECT_EQ(value, -1 * randomGradientValue);
    });

    nodeA->grad->forEach([=](int i, int j, float value){
        EXPECT_EQ(value, randomGradientValue);
    });
}


TEST(NodeOperations, node_multiplication)
{
    svf vectorA = {
        {-1.0, 2.0, -3.0, 4.0},
        {1.0, -2, 1, 3},
        {4, -3, 1, 1}
    };

    svf vectorB = {
        {4.0, 2.0},
        {-1.0, -5.0},  
        {2.0, 1.0},  
        {3.0, 1.0},  
    };

    std::shared_ptr<Mat> a = std::make_shared<Mat>(vectorA);
    std::shared_ptr<Node> nodeA = std::make_shared<Node>(a);

    std::shared_ptr<Mat> b = std::make_shared<Mat>(vectorB);
    std::shared_ptr<Node> nodeB = std::make_shared<Node>(b);

    std::shared_ptr<Node> c = nodeA * nodeB;
    svf randomGradientValue = {
        {-1, 4},
        {2, 7},
        {6, 5}
    };

    EXPECT_EQ(c->previous.size(), 2) << "The multiplication operator should have two children, one for each operand" << std::endl;


    c->grad = std::make_shared<Mat>(randomGradientValue);

    c->backward();

    svf expectedGradA = {
        {4, -19, 2, 1},
        {22, -37, 11, 13},
        {34, -31, 17, 23},  
    };

    svf expectedGradB = {
        {27,23},
        {-24,-21},
        {11,0},
        {8,42}
    };

    nodeA->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedGradA[i][j] - value) < 1e-3);
    });

    nodeB->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(expectedGradB[i][j] - value) < 1e-3);
    });
}

TEST(NodeOperations, node_division_test)
{
    svf a = {
        {-1, 4},
        {2, 7},
        {6, 5}
    };

    std::shared_ptr<Node> input = std::make_shared<Node>(
        std::make_shared<Mat>(a)
    );

    std::shared_ptr<Node> output = input / 2.0;

    svf expectedOutput = {
        {-0.5, 2.0},
        {1, 3.5},
        {3, 2.5}
    };

    output->data->forEach([=](int i, int j, float val){
        EXPECT_EQ(expectedOutput[i][j], val);
    }); 

    output->grad->assignValue(1.0);
    output->backward();
    
    input->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(value - 0.5) < 1e-3);
    });
}

TEST(NodeOperations, node_sum_test)
{
    svf a = {
        {-1, 4},
        {2, 7},
        {6, 5}
    };

    std::shared_ptr<Node> input = std::make_shared<Node>(
        std::make_shared<Mat>(a)
    );

    std::shared_ptr<Node> output = sum(input);

    EXPECT_EQ(output->data->at(0, 0), 23);

    output->grad->assignValue(1.0);
    output->backward();
    input->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(value - 1.0) < 1e-3);
    });
}