#include "core/algorithm.hpp"
#include "core/arch.hpp"
#include "core/data.hpp"
#include "core/stl.hpp"

#include <gtest/gtest.h>


using namespace core;


::testing::AssertionResult isEven(int N) {
  if (N % 2 == 0)
    return ::testing::AssertionSuccess() << N << " is even.";
  else
    return ::testing::AssertionFailure() << N << " is odd.";
}

TEST(GtestSkip, DoesSkip){
  GTEST_SKIP();
  EXPECT_EQ(0, 1);
}

class SkipFixture : public ::testing::Test {
  protected:
    void SetUp() {
      GTEST_SKIP() << "Skipping tests for this fixture.";

    }
};

TEST_F(SkipFixture, SkipOneTest){
  EXPECT_EQ(1, 2);
}

TEST_F(SkipFixture, SkipTwoTest) {
  EXPECT_TRUE(isEven(9));
}

TEST(OddityTest, IsEven) {
  EXPECT_TRUE(isEven(factorial(5)));
  EXPECT_TRUE(isEven(14));
  EXPECT_TRUE(isEven(factorial(7)));
}

////////////////////////////////////////////////////////

TEST(FactorialTest, FactorialOfFive) { ASSERT_EQ(factorial(5), 120); }

TEST(FactorialTest, HandlesZeroInput) { EXPECT_EQ(factorial(0), 1); }

class BinarySearchTestFixture : public ::testing::Test {
protected:
  void SetUp() override {
    names.insert(names.begin(),
                 {"elaine", "tifa", "aerith", "vanya", "zoe", "caitlyn"});
    std::sort(names.begin(), names.end());
  }
  std::vector<std::string> names;
};

TEST_F(BinarySearchTestFixture, ReturnsCorrectIndices) {
  EXPECT_EQ(binary_search(names, "tifa"), 3);
  EXPECT_EQ(binary_search(names, "ragnar"), -1);
  ::testing::StaticAssertTypeEq<int, decltype(binary_search(names, "aerith"))>();
}

class StackTestFixture : public ::testing::Test {
protected:
  void SetUp() override {
    s1.push(32);
    s1.push(11);
    s1.push(-7);
  }

  stack<int> s0;
  stack<int> s1;
  stack<int> s2;
};

TEST_F(StackTestFixture, StackIsEmptyInitially) {
  EXPECT_EQ(s0.size(), 0) << "Stack size is not zero.";
  EXPECT_EQ(s0.empty(), true) << "Stack should be empty";
}

TEST_F(StackTestFixture, PopWorks) {
  int n = s1.pop();
  EXPECT_EQ(n, -7);
  EXPECT_EQ(s1.size(), 2);
}

class DoubleListTestFixture : public ::testing::Test {
protected:
  void SetUp() override {}
  double_list<int> dlist1;
};

TEST_F(DoubleListTestFixture, InitialState) {
  ASSERT_EQ(dlist1.size(), 0);
  ASSERT_EQ(dlist1.empty(), true);
}

TEST_F(DoubleListTestFixture, PushbackTest) {
  dlist1.push_back(42);
  EXPECT_EQ(dlist1.back(), 42);
}

TEST_F(DoubleListTestFixture, PushFrontTest) {
  dlist1.push_front(11);
  EXPECT_EQ(dlist1.front(), 11);
}

//TEST_F(DoubleListTestFixture, PopfrontTest) {}

//TEST_F(DoubleListTestFixture, PopbackTest) {}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}