#include <identity.h>

#include "gtest/gtest.h"

#include <vector>

using ::testing::Test;

namespace testing {

namespace {
}

class IdentityTest : public Test {
  protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(IdentityTest, breathingTest)
{
    using namespace identity;
    Identity<int> i;
    Identity<long> l;
    Identity<char> c;

    Identity<std::vector<int>> vi;

}

}
