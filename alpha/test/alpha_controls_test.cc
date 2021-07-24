// MIT License
//
// Copyright (c) 2021 Emmanuel Godwin
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "alpha/core/controls.h"
#include "gtest/gtest.h"

using namespace blitz;

class FactorialTest : public ::testing::Test {
 protected:
  void SetUp() override {
    value1 = 8;
    value2 = -8;
  }
  long value1;
  long value2;
};

TEST_F(FactorialTest, FactorialOfValueLessThanZero) {
  ASSERT_EQ(alg::factorial(value2), 0);
}

TEST_F(FactorialTest, FactorialOfZero) { ASSERT_EQ(alg::factorial(0), 1); }

TEST_F(FactorialTest, FactorialOfOne) { ASSERT_EQ(alg::factorial(1), 1); }

TEST_F(FactorialTest, LogicalFactorialOfEight) {
  ASSERT_TRUE(alg::factorial(value1) == 40320);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}