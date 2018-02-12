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

template <typename T>
class Identity {
    T t;

    T const& value() const { return t; }

  public:
    Identity() : t(){};
    Identity(T const& t) : t(t){};

    template <typename U, typename Func>
    friend auto fmap(Identity<U> const& i, Func const& f);

    template <typename U, typename Func>
    friend auto bind(Identity<U> const& i, Func const& f);

    template <typename U>
    friend auto join(Identity<Identity<U>> i);

    template <typename U, typename V>
    friend bool operator==(Identity<U> t, Identity<V> u);

    template <typename U, typename V>
    friend bool operator!=(Identity<U> t, Identity<V> u);
};

// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================

template <typename T, typename Func>
auto fmap(Identity<T> const& i, Func const& f)
//    -> Identity<decltype(f(i.value()))>
{
    using U = std::invoke_result_t<Func, T>;
    // f is of type T -> U
    return Identity<U>{std::invoke(f, i.value())};
}

template <typename Func>
auto fmap(Func const& f)
{
    // maps (T -> U) -> (Identity<T> -> Identity<U>)
    return [=](auto t){return fmap(t, f);};
}

template <typename T>
struct template_parameter {};

template <typename T>
struct template_parameter<Identity<T>> {
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

template <typename Func>
auto bind(Func const& f)
{
    // lifts the argument into the monad and joins the result:
    // (T -> Identity<U>) -> (Identity<T> -> Identity<U>)
    return [=](auto t){return bind(t, f);};
}


template <typename T>
Identity<T> make(T t) {
    return Identity<T>{t};
}

template <typename T>
auto join(Identity<Identity<T>> i) {
    return Identity<T>{i.value()};
}

template <typename T, typename U>
bool operator==(Identity<T> t, Identity<U> u) {
    return t.value() == u.value();
}

template <typename T, typename U>
bool operator!=(Identity<T> t, Identity<U> u) {
    return t.value() != u.value();
}

} // namespace identity

#endif
