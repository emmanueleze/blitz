
#include "gtest/gtest.h"

#include "alpha/alpha.h"

using namespace alpha;

class SinglyListTest : public ::testing::Test {

 protected:
  void SetUp() override {
    
    list = new SinglyList<int>();
  
  }
  SinglyList<int>* list;
  
};

TEST_F(SinglyListTest, ListInitialState){
  EXPECT_EQ(list->size(), 0);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}