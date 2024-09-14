#include <gtest/gtest.h>
#include "../include/lab1.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(solve_func(30).first == 20 && solve_func(30).second == 40);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(solve_func(50).first == 45 && solve_func(50).second == 36);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 