// identity.h                                                         -*-C++-*-
#ifndef INCLUDED_IDENTITY
#define INCLUDED_IDENTITY

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
    -> Identity<decltype(f(i.value()))> {
    using Mapped = decltype(f(i.value()));
    return Identity<Mapped>{f(i.value())};
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
