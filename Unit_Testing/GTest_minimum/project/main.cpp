#include <gtest/gtest.h>

TEST(TestSuite, assertion1)
{
    EXPECT_STRNE("hello", "world");
}

TEST(TestSuite, assertion2)
{
    EXPECT_EQ(7 * 6, 1);
}

TEST(TestSuite, assertion3)
{
    ASSERT_EQ(1, 2) << "not equal numbers";
}
