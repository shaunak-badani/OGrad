#include <gtest/gtest.h>
#include "Model.h"
#include "Linear.h"
#include "MeanSquaredError.h"
#include "StaticLR.h"

struct ModelTest : testing::Test
{
    std::vector<std::shared_ptr<Layer>> layers;
    std::shared_ptr<LossFn> lossFn;

    // test input
    svf test_vec;
    std::shared_ptr<Node> test_node;

    // test output
    svf test_labels_vec;
    std::shared_ptr<Node> test_labels;

    std::shared_ptr<LearningRate> staticLR;

    void SetUp() override
    {
        layers.push_back(std::make_shared<Linear>(10, 1));
        lossFn = std::make_shared<MeanSquaredError>();

        test_vec = svf(5, std::vector<float>(10, 9.1));
        test_node = std::make_shared<Node>(
                std::make_shared<Mat>(test_vec)
            );

        test_labels_vec = svf(5, std::vector<float>(1, 1));
        test_labels = std::make_shared<Node>(
                std::make_shared<Mat>(test_labels_vec)
            );
        staticLR = std::make_shared<StaticLR>(0.2);
    }
    
    void TearDown() override
    {

    }
};

TEST_F(ModelTest, test_model_with_null_layer)
{
    std::shared_ptr<Layer> nullLayer;
    std::vector<std::shared_ptr<Layer>> nullLayers = {nullLayer};
    EXPECT_THROW(
        std::shared_ptr<Model> p = std::make_shared<Model>(nullLayers, lossFn, staticLR),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_with_null_loss)
{
    std::shared_ptr<LossFn> nullLossFn;
    EXPECT_THROW(
        std::shared_ptr<Model> p = std::make_shared<Model>(layers, nullLossFn, staticLR),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_with_null_learning_rate)
{
    std::shared_ptr<LearningRate> nullLearningRate;
    EXPECT_THROW(
        std::shared_ptr<Model> p = std::make_shared<Model>(layers, lossFn, nullLearningRate),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_with_incorrect_dimensions)
{
    std::shared_ptr<Model> model;
    layers.push_back(std::make_shared<Linear>(1, 3));
    model = std::make_shared<Model>(layers, lossFn, staticLR);
    std::shared_ptr<Node> loss;
    EXPECT_THROW(
        loss = model->forward(test_node, test_labels),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_with_incorrect_input_size_and_labels)
{
    std::shared_ptr<Model> model;
    layers.push_back(std::make_shared<Linear>(1, 3));
    model = std::make_shared<Model>(layers, lossFn, staticLR);

    svf incorrectInput = svf(6, std::vector<float>(10, 9.1));
    std::shared_ptr<Node> incorrectInputNode = std::make_shared<Node>(
        std::make_shared<Mat>(incorrectInput)
    );
    std::shared_ptr<Node> loss;
    EXPECT_THROW(
        loss = model->forward(incorrectInputNode, test_labels),
        std::runtime_error
    );

    svf incorrectLabels = svf(6, std::vector<float>(1, 1.1));
    std::shared_ptr<Node> incorrectLabelsNode = std::make_shared<Node>(
        std::make_shared<Mat>(incorrectLabels)
    );
    EXPECT_THROW(
        loss = model->forward(test_node, incorrectLabelsNode),
        std::runtime_error
    );
}

TEST_F(ModelTest, test_model_works_correctly)
{
    std::shared_ptr<Model> model;
    EXPECT_NO_THROW(
        model = std::make_shared<Model>(layers, lossFn, staticLR);
    );

    std::shared_ptr<Node> loss;
    EXPECT_NO_THROW(
        loss = model->forward(test_node, test_labels)
    );

    // Asserting loss is a scalar
    std::vector<int> lossShape = loss->data->getShape();
    EXPECT_EQ(lossShape.at(0), 1);
    EXPECT_EQ(lossShape.at(1), 1);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}