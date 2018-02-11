#include <identity.h>

#include "gtest/gtest.h"

#include <vector>

using ::testing::Test;

namespace testing {

namespace {}

class IdentityTest : public Test {
  protected:
    virtual void SetUp() {}

    virtual void TearDown() {}
};

TEST_F(IdentityTest, breathingTest) {
    using namespace identity;
    Identity<int>  i;
    Identity<long> l;
    Identity<char> c;

    Identity<std::vector<int>> vi;

    Identity<int> i2 = i;
    ASSERT_EQ(i2, i);

    const Identity<int> i3  = 3;
    Identity<int>       i3a = i3;
    Identity<int>       i3b;
    i3b = i3a;

    Identity<std::string> s1 = std::string{"test"};
    ASSERT_EQ(Identity<std::string>{std::string{"test"}}, s1);

    Identity<std::string> s2;
    s2 = s1;
    ASSERT_EQ(s2, s1);

    Identity<std::string> s3;
    s3 = std::move(s2);
    ASSERT_EQ(s3, s1);

    Identity<std::string> s4;
    ASSERT_EQ(s2, s4);

    ASSERT_NE(s2, s3);
}

TEST_F(IdentityTest, fmapTest) {
    using namespace identity;
    Identity<int>  i;
    Identity<long> l;
    Identity<char> c;

    auto twice = [](auto i) { return 2 * i; };
    auto i2    = fmap(i, twice);
    auto l2    = fmap(l, twice);
    auto c2    = fmap(c, twice);

    ASSERT_EQ(Identity{0}, i2);
    ASSERT_EQ(Identity{0L}, l2);
    ASSERT_EQ(Identity{'\0'}, c2);

    Identity<int>  i3(3);
    Identity<long> l3(3);
    Identity<char> c3(3);

    auto i6 = fmap(i3, twice);
    auto l6 = fmap(l3, twice);
    auto c6 = fmap(c3, twice);

    ASSERT_EQ(Identity{6}, i6);
    ASSERT_EQ(Identity{6L}, l6);
    ASSERT_EQ(Identity{'\6'}, c6);

    ASSERT_EQ(Identity<int>{6}, i6);
    ASSERT_EQ(Identity<int>{6}, l6);
}

TEST_F(IdentityTest, bindTest) {
    using namespace identity;
    Identity<int>  i;
    Identity<long> l;
    Identity<char> c;

    auto twice = [](auto i) -> Identity<decltype(2 * i)> { return 2 * i; };
    auto i2    = bind(i, twice);
    auto l2    = bind(l, twice);
    auto c2    = bind(c, twice);

    ASSERT_EQ(Identity{0}, i2);
    ASSERT_EQ(Identity{0L}, l2);
    ASSERT_EQ(Identity{'\0'}, c2);

    Identity<int>  i3(3);
    Identity<long> l3(3);
    Identity<char> c3(3);

    auto i6 = bind(i3, twice);
    auto l6 = bind(l3, twice);
    auto c6 = bind(c3, twice);

    ASSERT_EQ(Identity{6}, i6);
    ASSERT_EQ(Identity{6L}, l6);
    ASSERT_EQ(Identity{'\6'}, c6);

    ASSERT_EQ(Identity<int>{6}, i6);
    ASSERT_EQ(Identity<int>{6}, l6);
}

TEST_F(IdentityTest, joinTest) {
    using namespace identity;
    Identity<int>           i  = make(1);
    Identity<Identity<int>> ii = make(i);
    Identity<int>           j  = join(ii);

    ASSERT_EQ(Identity{1}, i);
    ASSERT_EQ(Identity{1}, j);
}
} // namespace testing
