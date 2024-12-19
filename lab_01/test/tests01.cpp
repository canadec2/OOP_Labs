#include <gtest/gtest.h>
#include <string>
#include "../include/solution.h"

TEST(BracketTest, BasicCases) {
    EXPECT_EQ(isValid("()"), true);
    EXPECT_EQ(isValid("())"), false);
    EXPECT_EQ(isValid("(("), false);
    EXPECT_EQ(isValid(")"), false);
    EXPECT_EQ(isValid(""), true);
}

TEST(BracketTest, EdgeCases) {
    EXPECT_EQ(isValid("("), false);
    EXPECT_EQ(isValid(")"), false);
    EXPECT_EQ(isValid(""), true);
}

TEST(BracketTest, ComplexCases) {
    EXPECT_EQ(isValid("(((())))"), true);
    EXPECT_EQ(isValid("()()()"), true);
    EXPECT_EQ(isValid("((())"), false);
    EXPECT_EQ(isValid("(()))"), false);
}

TEST(BracketTest, LargeInput) {
    std::string largeInput(100, '(');
    largeInput += std::string(100, ')');
    EXPECT_EQ(isValid(largeInput), true);

    largeInput[99] = ')';
    EXPECT_EQ(isValid(largeInput), false);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
