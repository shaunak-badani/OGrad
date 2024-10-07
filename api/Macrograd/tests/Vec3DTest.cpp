#include "Vec3D.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

struct Vec3DTest : public testing::Test
{
    std::vector<svf> a = 
    {
        {
            {1.0, 2.0, 3.0}, {-1.0, 2.0, -3.0}, {9.0, -19.0, 8.0}
        },
        {
            {1.8, 3.4, 9.8}, {9.1, 1.2, 4.2}, {0.8, 11.1, -100.2}
        },
    };

    std::shared_ptr<Vec3D> A;

    void SetUp() override
    {
       A = std::make_shared<Vec3D>(a);
    }
};

TEST_F(Vec3DTest, test_initialized_correctly)
{
    std::vector<int> p = A->getShape();

    EXPECT_THAT(p, testing::ElementsAre(2, 3, 3));

    EXPECT_THROW(A->getMatAt(2), std::runtime_error);

    EXPECT_NO_THROW(A->getMatAt(1));
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}