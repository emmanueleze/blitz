#include "alpha/core/arch.h"

#include <gtest/gtest.h>

using namespace alpha;

using factory = ComponentFactory;
using CType::ENGINE;
using CType::PISTON;
using CType::NONE;

class ComponentFactoryTest : public ::testing::Test {
 protected:
  void SetUp() override {
    e0 = factory::create("Aelos", ENGINE);
    e1 = factory::create();
  }
  GenericComponent e0;
  GenericComponent e1;

};

TEST_F(ComponentFactoryTest, ComponentNameAndTypeMatch) {
  ASSERT_TRUE((e0.name() == "Aelos") && (e0.type() == ENGINE)) <<
  "Component name and type mismatch";
}

TEST_F(ComponentFactoryTest, ComponentWithNoArgs){
  EXPECT_EQ(e1.type(),  NONE);
  EXPECT_EQ(e1.name(), "Generic");
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}