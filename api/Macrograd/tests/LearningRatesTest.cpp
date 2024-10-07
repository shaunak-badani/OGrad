#include "LearningRate.h"
#include "StaticLR.h"
#include <gtest/gtest.h>

struct LRTest : testing::Test
{
    std::shared_ptr<LearningRate> staticLR;
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

TEST_F(LRTest, test_static_lr)
{
    float learningRate = 0.02;
    staticLR = std::make_shared<StaticLR>(learningRate);
    EXPECT_FLOAT_EQ(staticLR->getLearningRate(1.0), 0.02);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}