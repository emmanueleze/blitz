#include "core/arch.hpp"

#include <gtest/gtest.h>

TEST(AllTests, NoeTest) {
  EXPECT_FALSE((5-1) < 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}