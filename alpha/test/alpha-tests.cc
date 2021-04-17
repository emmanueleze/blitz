
#include <gtest/gtest.h>
#include "alpha.h"

using namespace blitz;
using namespace blitz::gen;

class NameTest : public ::testing::Test{
    protected:
        void SetUp()override{
            Name lori {"Lori", "Trumann"};
            _name = lori;
        }
        Name _name;
};

TEST_F(NameTest, LogicalTest){
    ASSERT_TRUE((_name.FirstName() == "Lori") &&
        (_name.LastName() == "Trumann") );
}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}