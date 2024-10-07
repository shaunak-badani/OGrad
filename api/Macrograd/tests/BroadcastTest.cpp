#include <gtest/gtest.h>
#include "Broadcast.h"

struct BroadcastTest : public testing::Test
{
    svf a = {{0.4, 0.2, 5.6}, {2.1, 10.8, -27.6}}; // 2 x 3
    svf b = {{0.088}}; // 1 x 1
    svf c = {{1, 189.3, -90.3344}}; // 1 x 3
    svf d = {{2.3, 4.5}}; // 1 x 2

    std::shared_ptr<Node> A, B, C, D;

    void SetUp() override
    {
        A = std::make_shared<Node>(std::make_shared<Mat>(a));
        B = std::make_shared<Node>(std::make_shared<Mat>(b));
        C = std::make_shared<Node>(std::make_shared<Mat>(c));
        D = std::make_shared<Node>(std::make_shared<Mat>(d));
    }
};


TEST_F(BroadcastTest, test_broadcast_throws_error)
{
    std::shared_ptr<Broadcast::Add> add = std::make_shared<Broadcast::Add>();
    EXPECT_THROW(add->calculate(B, D), std::runtime_error);
    EXPECT_THROW(add->calculate(C, D), std::runtime_error);
    EXPECT_THROW(add->calculate(A, B), std::runtime_error);
}

TEST_F(BroadcastTest, test_broadcast_works_as_expected)
{
    std::shared_ptr<Broadcast::Add> add = std::make_shared<Broadcast::Add>();
    std::shared_ptr<Node> out;
    EXPECT_NO_THROW(out = add->calculate(A, C));

    svf expectedOutput = {{1.4, 189.5, -84.7344}, {3.1, 200.1, -117.9344}};

    out->data->forEach([=](int i, int j, float value){
        EXPECT_FLOAT_EQ(value, expectedOutput[i][j]);
    });

    float randomGradientValue = 9.34;

    out->grad->assignValue(randomGradientValue);
    out->backward();

    C->grad->forEach([=](int i, int j, float value){
        EXPECT_FLOAT_EQ(value, 2 * randomGradientValue);
    });

    A->grad->forEach([=](int i, int j, float value){
        EXPECT_FLOAT_EQ(value, randomGradientValue);
    });
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}