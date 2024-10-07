#include <gtest/gtest.h>
#include "Linear.h"
#include "MeanSquaredError.h"
#include "Model.h"
#include "Node.h"
#include "ModelBuilder.h"
#include "StaticLR.h"

struct ModelBuilderTest : testing::Test
{
    std::vector<std::shared_ptr<Layer>> layers;
    std::shared_ptr<LossFn> lossFn;
    std::shared_ptr<LearningRate> lr;
    std::shared_ptr<ModelBuilder> modelBuilder;

    // test input
    svf test_vec;
    std::shared_ptr<Node> test_node;

    // test output
    svf test_labels_vec;
    std::shared_ptr<Node> test_labels;

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
        // learning rate has to be < 0.0002, else this doesn't work
        lr = std::make_shared<StaticLR>(0.0001);
        modelBuilder = std::make_shared<ModelBuilder>();
    }
    
    void TearDown() override
    {

    }
};


TEST_F(ModelBuilderTest, test_build_model_exceptions)
{
    // without any parameters
    EXPECT_THROW(
        modelBuilder->build(),
        std::runtime_error
    );

    // with only loss fn, will throw error while creation, since no learning rate is defined.
    modelBuilder->setLossFn(lossFn);
    EXPECT_THROW(
        modelBuilder->build(),
        std::runtime_error
    );

    // with standard layer and loss fn
    // will throw an error because there's no learning rate
    modelBuilder->addLayer(layers.front());
    EXPECT_THROW(
        modelBuilder->build(),
        std::runtime_error
    );

    //assign a learning rate
    modelBuilder->setLearningRate(lr);
    EXPECT_NO_THROW(
        modelBuilder->build()
    );


    // with null layers
    std::shared_ptr<Layer> nullLayer;
    modelBuilder->addLayer(nullLayer);
    EXPECT_THROW(
        modelBuilder->build(),
        std::runtime_error
    );
}

TEST_F(ModelBuilderTest, test_model_train_with_one_epoch)
{

    modelBuilder->addLayer(layers.front());
    modelBuilder->setLossFn(lossFn);
    modelBuilder->setLearningRate(lr);

    std::shared_ptr<Model> model = modelBuilder->build();

    std::shared_ptr<Node> loss = model->forward(test_node, test_labels);

    std::vector<std::shared_ptr<Node>> params = model->parameters();
    float initialLoss = loss->data->at(0, 0);
    model->train(test_node->data, test_labels->data, 0);
    params = model->parameters();

    for(std::shared_ptr<Node> param : params)
    {
        param->grad->forEach([=](int i, int j, float value){
            EXPECT_FLOAT_EQ(value, 0.0);
        });
    }

    float lossAfter = model->forward(test_node, test_labels)->data->at(0, 0);

    EXPECT_LE(lossAfter, initialLoss);

    
    
}