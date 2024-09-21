#include <gtest/gtest.h>
#include <string>
#include "../include/solution.h"  // Предположим, что функция isValid находится в этом файле

TEST(BracketTest, BasicCases) {
    EXPECT_EQ(isValid("()"), true);
    EXPECT_EQ(isValid("()()"), true);
    EXPECT_EQ(isValid("(())"), true);
    EXPECT_EQ(isValid(")("), false);
    EXPECT_EQ(isValid("(()"), false);
    EXPECT_EQ(isValid("())"), false);
}

TEST(BracketTest, EdgeCases) {
    EXPECT_EQ(isValid(""), true);  // Пустая строка считается сбалансированной
    EXPECT_EQ(isValid("("), false);  // Одна открывающая скобка
    EXPECT_EQ(isValid(")"), false);  // Одна закрывающая скобка
}

TEST(BracketTest, ComplexCases) {
    EXPECT_EQ(isValid("(((())))"), true);  // Правильная сложная последовательность
    EXPECT_EQ(isValid("((())())"), true);  // Еще одна сложная правильная последовательность
    EXPECT_EQ(isValid("(()))(()"), false);  // Неправильная последовательность
    EXPECT_EQ((isValid("((())")) , false);  // Отсутствует закрывающая скобка
}

TEST(BracketTest, LargeInput) {
    std::string largeInput(100, '(');
    largeInput += std::string(100, ')');
    EXPECT_EQ(isValid(largeInput), true);  // Большая правильная строка
    
    largeInput[99] = ')';  // Изменим одну скобку
    EXPECT_EQ(isValid(largeInput), false);  // Теперь строка неправильная
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
