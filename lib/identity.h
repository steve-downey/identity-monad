// identity.h                                                         -*-C++-*-
#ifndef INCLUDED_IDENTITY
#define INCLUDED_IDENTITY

#include <type_traits>
#include <functional>

//@PURPOSE:
//
//@CLASSES:
//
//@AUTHOR: Steve Downey (sdowney@gmail.com)
//
//@DESCRIPTION: Identity Monad


namespace identity {

template<typename T>
class Identity
{
    T t;
  public:
    Identity() : t() {};
    Identity(T const& t) : t(t) {};

    T value() {return t;}
    T const& value() const {return t;}
};

template <typename T, typename Func>
auto fmap(Identity<T> const& i, Func const& f)
    //    -> Identity<decltype(f(i.value()))>
{
    using U = std::invoke_result_t<Func, T>;
    // f is of type T -> U
    return Identity<U>{std::invoke(f, i.value())};
}

template<typename T>
struct template_parameter
{
};

template<typename T>
struct template_parameter<Identity<T>>
{
    typedef T type;
};

template <typename T, typename Func>
auto bind(Identity<T> const& i, Func const& f)
    //    -> std::invoke_result_t<Func, T>
{
    using M = std::invoke_result_t<Func, T>;
    using U = typename template_parameter<M>::type;
    // assert that f is of type T -> Identity<U>
    static_assert(std::is_invocable_r<Identity<U>, Func, T>::value);
    // so unwrap i and call f on it
    return std::invoke(f, i.value());
}

template<typename T, typename U>
bool operator==(Identity<T> t, Identity<U> u) {
    return t.value() == u.value();
}

template<typename T, typename U>
bool operator!=(Identity<T> t, Identity<U> u) {
    return t.value() != u.value();
}

// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================


}  // close package namespace

#endif
