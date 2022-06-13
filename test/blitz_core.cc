#include "core/data.hpp"
#include "core/algorithm.hpp"
#include "core/arch.hpp"
#include "core/stl.hpp"

#include <gtest/gtest.h>

using namespace core;


::testing::AssertionResult isEven(int N) {
  if(N % 2 == 0)
    return ::testing::AssertionSuccess() << N << " is even.";
  else
    return ::testing::AssertionFailure() << N << " is odd.";
}

TEST(OddityTest, IsEven) {
  EXPECT_TRUE(isEven(factorial(5)));
  EXPECT_TRUE(isEven(13));
  EXPECT_TRUE(isEven(factorial(7)));
}


TEST(FactorialTest, FactorialOfFive){
  ASSERT_EQ(factorial(5), 120);
}

TEST(FactorialTest, HandlesZeroInput){
  EXPECT_EQ(factorial(0), 1);
}

TEST(TwoSumTest, RandomIndices) {
  std::vector<int> coll {1,2,5,7,8,11};
  auto result = two_sum(coll, 15);

  EXPECT_EQ(result[0], 3);
  EXPECT_EQ(result.at(1), 4);
}


class StackTestFixture : public ::testing::Test {
protected:
  void SetUp()override{
    s1.push(32);
    s1.push(11);
    s1.push(-7);
  }
  
  stack<int> s0;
  stack<int> s1;
  stack<int> s2;
};

TEST_F(StackTestFixture, StackIsEmptyInitially){
  EXPECT_EQ(s0.size(), 0) << "Stack size is not zero.";
  EXPECT_EQ(s0.empty(), true) << "Stack should be empty";
}

TEST_F(StackTestFixture, PopWorks) {
  int n = s1.pop();
  EXPECT_EQ(n, -7);
  EXPECT_EQ(s1.size(), 2);
}

TEST(NewSuite, Pred){
  EXPECT_PRED1(greaterthanzero(), 2);
}




int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}