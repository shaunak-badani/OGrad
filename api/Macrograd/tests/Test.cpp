#include <iostream>
#include "IOUtils.h"
#include <gtest/gtest.h>

TEST(IOUtils, split_string)
{
    std::string stringToSeparate = "Today,was,a,good,day";

    std::vector<std::string> separatedString = IOUtils::split_comma_separated_string(stringToSeparate);

    std::vector<std::string> expectedVector = {"Today", "was", "a", "good", "day"};

    ASSERT_EQ(separatedString.size(), expectedVector.size()) << "Expected size does not match actual size";

    int actualLength = separatedString.size();
    for(int index = 0 ; index < actualLength ; index++)
    {
        EXPECT_STREQ(expectedVector[index].c_str(), separatedString[index].c_str());
    }
}

TEST(IOUtils, string_to_float_vector)
{
    std::vector<std::string> stringVector = {"1","89","903.24", "-901"," 90.21\n"};

    std::vector<float> expectedFloatVector = {1, 89, 903.24, -901, 90.21};

    std::vector<float> actualVector = IOUtils::to_float(stringVector);

    ASSERT_EQ(actualVector.size(), expectedFloatVector.size()) << "Expected vector size does not match actual vector size";

    int actualLength = actualVector.size();
    for(int index = 0 ; index < actualLength ; index++)
    {
        EXPECT_EQ(expectedFloatVector[index], actualVector[index]);
    }
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}