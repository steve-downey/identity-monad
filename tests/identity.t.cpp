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

    auto twice = [](auto z) { return 2 * z; };
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

identity::Identity<int> identCopy(identity::Identity<int> a) {return a;}

TEST_F(IdentityTest, makeTest) {
    using namespace identity;
    Identity<int> r = identCopy(Identity<int>{3});
    Identity<int> r2 = identCopy(make(3));
    ASSERT_EQ(r, r2);
}

TEST_F(IdentityTest, make2Test) {
    using namespace identity;
    Identity<int> r = identCopy(Identity<int>{3});
    Identity<int> r2 = identCopy(make<Identity>(3));
    ASSERT_EQ(r, r2);
    Identity<int>           i  = make<Identity>(1);
    Identity<Identity<int>> ii = make<Identity>(i);
    ASSERT_EQ(Identity<Identity<int>>{Identity{1}}, ii);

}

TEST_F(IdentityTest, joinTest) {
    using namespace identity;
    Identity<int>           i  = make(1);
    Identity<Identity<int>> ii = make(i);
    Identity<int>           j  = join(ii);

    ASSERT_EQ(Identity{1}, i);
    ASSERT_EQ(Identity{1}, j);
}


TEST_F(IdentityTest, fmapHigherOrderTest) {
    using namespace identity;
    Identity<int>  i;
    Identity<long> l;
    Identity<char> c;

    auto twice     = [](auto i) { return 2 * i; };
    auto fmapTwice = fmap(twice);

    auto i2 = fmapTwice(i);
    auto l2 = fmapTwice(l);
    auto c2 = fmapTwice(c);

    ASSERT_EQ(Identity{0}, i2);
    ASSERT_EQ(Identity{0L}, l2);
    ASSERT_EQ(Identity{'\0'}, c2);

    Identity<int>  i3(3);
    Identity<long> l3(3);
    Identity<char> c3(3);

    auto i6 = fmapTwice(i3);
    auto l6 = fmapTwice(l3);
    auto c6 = fmapTwice(c3);

    ASSERT_EQ(Identity{6}, i6);
    ASSERT_EQ(Identity{6L}, l6);
    ASSERT_EQ(Identity{'\6'}, c6);

    ASSERT_EQ(Identity<int>{6}, i6);
    ASSERT_EQ(Identity<int>{6}, l6);
}

TEST_F(IdentityTest, bindHigherOrderTest) {
    using namespace identity;
    Identity<int>  i;
    Identity<long> l;
    Identity<char> c;

    auto twice     = [](auto i) -> Identity<decltype(2 * i)> { return 2 * i; };
    auto bindTwice = bind(twice);

    auto i2 = bindTwice(i);
    auto l2 = bindTwice(l);
    auto c2 = bindTwice(c);

    ASSERT_EQ(Identity{0}, i2);
    ASSERT_EQ(Identity{0L}, l2);
    ASSERT_EQ(Identity{'\0'}, c2);

    Identity<int>  i3(3);
    Identity<long> l3(3);
    Identity<char> c3(3);

    auto i6 = bindTwice(i3);
    auto l6 = bindTwice(l3);
    auto c6 = bindTwice(c3);

    ASSERT_EQ(Identity{6}, i6);
    ASSERT_EQ(Identity{6L}, l6);
    ASSERT_EQ(Identity{'\6'}, c6);

    ASSERT_EQ(Identity<int>{6}, i6);
    ASSERT_EQ(Identity<int>{6}, l6);
}

int six(int a, int b, int c, int d, int e, int f) {
    return a + b + c + d + e + f;
}

TEST_F(IdentityTest, curryTest) {
    using namespace identity;
    auto c  = curry(six);
    int  i1 = c(1)(2)(3)(4)(5)(6);

    ASSERT_EQ(21, i1);
}

int two(int a) { return a; }

int three(int a, int b) { return a + b; }

TEST_F(IdentityTest, apTest) {
    using namespace identity;
    auto f = [](int a) {return [a](int b){return three(a,b);};};
    // f is of type int -> (int -> int)
    Identity<int> i3(3);
    auto partial = fmap(i3, f);
    // partial is Identity<int -> int> (roughly)
    Identity<int> i4(4);
    Identity<int> k = ap(partial, i4);
    ASSERT_EQ(Identity<int>(7), k);

    auto curry1 = [](auto func) {
        return [func](int a) {
            return [func, a](int b) {
                return func(a, b);
            };
        };
    };
    auto g = curry1(three);
    auto h = g(3);
    ASSERT_EQ(7, h(4));

    auto partial2 = fmap(i3, g);
    Identity<int> k2 = ap(partial2, i4);
    ASSERT_EQ(Identity<int>(7), k2);

}

TEST_F(IdentityTest, apTest2) {
    using namespace identity;
    auto f = [](int a) { return [a](int b) { return a + b; }; };
    // f is of type int -> (int -> int)
    Identity<int> i3(3);
    auto          partial = fmap(i3, f);
    // partial is Identity<int -> int> (roughly)
    Identity<int> i4(4);
    Identity<int> k = ap<Identity>(partial, i4);
    ASSERT_EQ(Identity<int>(7), k);

    auto curry1 = [](auto func) {
        return
            [func](int a) { return [func, a](int b) { return func(a, b); }; };
    };
    auto g = curry1(three);
    auto h = g(3);
    ASSERT_EQ(7, h(4));

    auto          partial2 = fmap(i3, g);
    Identity<int> k2       = ap<Identity>(partial2, i4);
    ASSERT_EQ(Identity<int>(7), k2);
}

template <template <typename> typename Ap, typename Value>
void genericTest() {
    using namespace identity;
    auto f = [](int a) { return [a](int b) { return a + b; }; };
    // f is of type int -> (int -> int)
    auto i3      = make<Ap>(3);
    auto partial = fmap(i3, f);
    // partial is Identity<int -> int> (roughly)
    auto      i4 = make<Ap>(4);
    Ap<Value> k  = ap<Ap>(partial, i4);
    ASSERT_EQ(Ap<Value>(7), k);

    auto curry1 = [](auto func) {
        return
            [func](int a) { return [func, a](int b) { return func(a, b); }; };
    };
    auto g = curry1(three);
    auto h = g(3);
    ASSERT_EQ(7, h(4));

    auto      partial2 = fmap(i3, g);
    Ap<Value> k2       = ap<Ap>(partial2, i4);
    ASSERT_EQ(Ap<Value>(7), k2);
}

TEST_F(IdentityTest, apTest3) {
    genericTest<identity::Identity, int>();
}
} // namespace testing
