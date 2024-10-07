#include <gtest/gtest.h>
#include "LossFn.h"
#include "MeanSquaredError.h"
#include "RootMeanSquaredError.h"
#include "Node.h"
#include "Mat.h"
#include "LayerUtils.h"
#include "SoftmaxCrossEntropyLoss.h"

struct LossFnTest : public testing::Test
{
    svf a;
    svf b;
    std::shared_ptr<Node> nodeA;
    std::shared_ptr<Node> nodeB;

    void SetUp() override
    {
        a = {{-1.5}, {2.4}, {3.3}, {1.9}, {2.8}};

        b = {{7.6}, {-1.1}, {4.2}, {-3.2}, {10.0}};

        nodeA = std::make_shared<Node>(
            std::make_shared<Mat>(a)
        );

        nodeB = std::make_shared<Node>(
            std::make_shared<Mat>(b)
        );
    }

    void TearDown() override
    {
    }
};

TEST_F(LossFnTest, MeanSquaredError)
{
    std::shared_ptr<LossFn> lossFn = std::make_shared<MeanSquaredError>();
    std::shared_ptr<Node> output = (*lossFn.get())(nodeA, nodeB);

    float expectedLoss = 173.72;
    std::vector<int> outputShape = output->data->getShape();

    ASSERT_EQ(outputShape.at(0), 1) << "Loss output should have only 1 row" << std::endl;

    ASSERT_EQ(outputShape.at(1), 1) << "Loss output should have only 1 column" << std::endl;
    ASSERT_TRUE(abs(expectedLoss - output->data->at(0,0))< 1e-3);

    output->grad->assignValue(1.0);

    std::shared_ptr<LayerUtils> layerUtils = std::make_shared<LayerUtils>();
    layerUtils->backward(output);

    svf expectedGradA = { {-18.2}, {7.0}, {-1.8}, {10.2}, {-14.4} };

    nodeA->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(value - expectedGradA[i][j]) < 1e-3);
    });

    // nodeB grad = -nodeA grad
    nodeB->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(value - (-expectedGradA[i][j])) < 1e-3);
    });

}

TEST_F(LossFnTest, RootMeanSquaredError)
{
    std::shared_ptr<LossFn> lossFn = std::make_shared<RootMeanSquaredError>();
    std::shared_ptr<Node> output = (*lossFn.get())(nodeA, nodeB);

    float expectedLoss = 5.8944;
    std::vector<int> outputShape = output->data->getShape();

    ASSERT_EQ(outputShape.at(0), 1) << "Loss output should have only 1 row" << std::endl;

    ASSERT_EQ(outputShape.at(1), 1) << "Loss output should have only 1 column" << std::endl;

    ASSERT_TRUE(abs(expectedLoss - output->data->at(0, 0)) < 1e-3);

    output->grad->assignValue(1.0);
    std::shared_ptr<LayerUtils> layerUtils = std::make_shared<LayerUtils>();
    layerUtils->backward(output);

    svf expectedGradA = {
        {(0.5f / expectedLoss) * (2 * (-9.1f) / 5)},
        {(0.5f / expectedLoss) * (2 * 3.5f / 5)},
        {(0.5f / expectedLoss) * (2 * (-0.9f) / 5)},
        {(0.5f / expectedLoss) * (2 * (5.1f) / 5)},
        {(0.5f / expectedLoss) * (2 * (-7.2f) / 5)}
    };

    nodeA->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(value - expectedGradA[i][j]) < 1e-3);
    });

    // nodeB grad = -nodeA grad
    nodeB->grad->forEach([=](int i, int j, float value){
        EXPECT_TRUE(abs(value - (-expectedGradA[i][j])) < 1e-3);
    });
}

TEST(SoftmaxTest, softmax_with_ce_test)
{
    svf actualValues = {{0.1, -3.445, 10}, {9, -4.5, 2.2}};
    svf expectedValues = {{0, 1, 0}, {0, 0, 1}};

    std::shared_ptr<Node> actual = std::make_shared<Node>(
        std::make_shared<Mat>(actualValues)
    );

    std::shared_ptr<Node> expected = std::make_shared<Node>(
        std::make_shared<Mat>(expectedValues)
    );

    std::shared_ptr<LossFn> loss = std::make_shared<SoftmaxCrossEntropyLoss>();
    std::shared_ptr<Node> output = (*loss.get())(actual, expected);
    std::vector<int> outputShape = output->data->getShape();

    ASSERT_EQ(outputShape.at(0), 1) << "Loss output should have only 1 row" << std::endl;

    ASSERT_EQ(outputShape.at(1), 1) << "Loss output should have only 1 column" << std::endl;
    float expectedLoss = 10.1231;
    ASSERT_NEAR(expectedLoss, output->data->at(0, 0), 1e-3);

    output->grad->assignValue(1.0);
    output->backward();

    svf expectedGrad = {{2.5086e-05, -5.0000e-01,  4.9997e-01},
        {4.9944e-01,  6.8472e-07, -4.9944e-01}};
    
    actual->grad->forEach([=](int i, int j, float value){
        EXPECT_NEAR(value, expectedGrad[i][j], 1e-5);
    });
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
