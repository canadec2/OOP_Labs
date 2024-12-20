#include <gtest/gtest.h>
#include "../include/Octal.hpp"

TEST(OctalTest, DefaultConstructor)
{
  Octal num;
  EXPECT_EQ(num.Size(), 0);
  EXPECT_EQ(num.Capacity(), 0);
  EXPECT_EQ(num.toString(), "");
}

TEST(OctalTest, ParamConstructor)
{
  Octal num(5, 3);
  EXPECT_EQ(num.Size(), 5);
  EXPECT_EQ(num.Capacity(), 5);
  EXPECT_EQ(num.toString(), "33333");
}

TEST(OctalTest, StringConstructor)
{
  Octal num("123");
  EXPECT_EQ(num.Size(), 3);
  EXPECT_EQ(num.Capacity(), 3);
  EXPECT_EQ(num.toString(), "123");
}

TEST(OctalTest, CopyConstructor)
{
  Octal original("123");
  Octal copy(original);
  EXPECT_EQ(copy.Size(), 3);
  EXPECT_EQ(copy.Capacity(), 3);
  EXPECT_EQ(copy.toString(), "123");
  copy.push_back(4);
  EXPECT_EQ(original.toString(), "123");
  EXPECT_EQ(copy.toString(), "4123");
}

TEST(OctalTest, MoveConstructor)
{
  Octal original("123");
  Octal moved(std::move(original));
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Capacity(), 3);
  EXPECT_EQ(moved.toString(), "123");
  EXPECT_EQ(original.Size(), 0);
  EXPECT_EQ(original.Capacity(), 0);
  EXPECT_EQ(original.toString(), "");
}

TEST(OctalTest, CopyAssignment)
{
  Octal original("123");
  Octal copy;
  copy = original;
  EXPECT_EQ(copy.Size(), 3);
  EXPECT_EQ(copy.Capacity(), 3);
  EXPECT_EQ(copy.toString(), "123");
  copy.push_back(4);
  EXPECT_EQ(original.toString(), "123");
  EXPECT_EQ(copy.toString(), "4123");
}

TEST(OctalTest, MoveAssignment)
{
  Octal original("123");
  Octal moved;
  moved = std::move(original);
  EXPECT_EQ(moved.Size(), 3);
  EXPECT_EQ(moved.Capacity(), 3);
  EXPECT_EQ(moved.toString(), "123");
  EXPECT_EQ(original.Size(), 0);
  EXPECT_EQ(original.Capacity(), 0);
  EXPECT_EQ(original.toString(), "");
}

TEST(OctalTest, DestructorTest)
{
  Octal *num = new Octal("123");
  EXPECT_EQ(num->Size(), 3);
  EXPECT_EQ(num->toString(), "123");
  delete num;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}