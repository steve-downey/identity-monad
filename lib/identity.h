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
    Identity() : t() {}
    Identity(T const& t) : t(t) {}
};


// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================


}  // close package namespace

#endif
