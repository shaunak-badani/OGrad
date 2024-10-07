#include <gtest/gtest.h>
#include "Linear.h"
#include "Layer.h"

struct LayersTest : public testing::Test
{
    svf identity = svf(10, std::vector<float>(10, 0));
    std::shared_ptr<Node> identityNode;
    std::shared_ptr<Layer> layer = std::make_shared<Linear>(10, 3);


    void SetUp() override
    {
        for(int i = 0 ; i < 10 ; i++)
        {
            for(int j = 0 ; j < 10 ; j++)
            {
                identity[i][j] = (i == j);
            }
        }
        identityNode = std::make_shared<Node>(
            std::make_shared<Mat>(identity)
        );
    }

    void TearDown() override
    {

    }
};

TEST_F(LayersTest, test_layers_initialized_properly)
{

    std::shared_ptr<Node> layerWeights = layer->forward(identityNode);

    layerWeights->data->forEach([=](int i, int j, float value){
        EXPECT_LE(value, 1.0);
        EXPECT_GE(value, -1.0);
    });

    std::vector<std::shared_ptr<Node>> params = layer->getParameters();

    // weights and biases
    EXPECT_EQ(params.size(), 2);
}


int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}