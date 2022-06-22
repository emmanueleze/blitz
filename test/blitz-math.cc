#include "math/mat.hpp"
#include "math/vector.hpp"

#include <gtest/gtest.h>


using namespace math;

class MatrixFixture : public ::testing::Test {
  protected:
    void SetUp() {

    }
  mat<int,3,3> m0;
};

TEST_F(MatrixFixture, InitialTest) {
  EXPECT_EQ(m0.size().first, 3);
  EXPECT_EQ(m0.size().second, 3);
  EXPECT_EQ(sizeof(m0._data), sizeof(int)*9);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}