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

TEST_F(IdentityTest, fmapTest)
{
    using namespace identity;
    Identity<int> i;
    Identity<long> l;
    Identity<char> c;

    auto twice = [](auto i) {return 2*i;};
    auto i2 = fmap(i, twice);
    auto l2 = fmap(l, twice);
    auto c2 = fmap(c, twice);

    ASSERT_EQ(0, i2.value());
    ASSERT_EQ(0, l2.value());
    ASSERT_EQ(0, c2.value());

    Identity<int> i3(3);
    Identity<long> l3(3);
    Identity<char> c3(3);

    auto i6 = fmap(i3, twice);
    auto l6 = fmap(l3, twice);
    auto c6 = fmap(c3, twice);

    ASSERT_EQ(6, i6.value());
    ASSERT_EQ(6, l6.value());
    ASSERT_EQ(6, c6.value());

    ASSERT_EQ(Identity<int>{6}, i6);
    ASSERT_EQ(Identity<int>{6}, l6);
}

}
