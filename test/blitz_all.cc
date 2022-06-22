#include "blitz.hpp"

#include <gtest/gtest.h>

using namespace blitz;

TEST(IntervalTest, CloseInterval) {
  EXPECT_TRUE(in_range(7, 0, 9));
  EXPECT_TRUE(in_range(0, -1, 1));
  EXPECT_FALSE(in_range(0.5, 1.0, 1.5));
  EXPECT_FALSE(in_range(8, -5, -1, Interval::Closed));
}

TEST(IntervalTest, OpenInterval) {
  EXPECT_FALSE(in_range(0, 0, 1, Interval::Open));
  EXPECT_TRUE(in_range(0, -1, 1, Interval::Open));
  EXPECT_FALSE(in_range(2, 2, 3, Interval::Open));
}

TEST(IntervalTest, CloseOpenInterval) {
  EXPECT_TRUE(in_range(0, 0, 5, Interval::ClosedOpen));
}

TEST(IntervalTest, OpenClosedInterval) {
  EXPECT_TRUE(in_range(3, 0, 3, Interval::OpenClosed));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}