//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/conversion/type_traits/is_destructible.hpp>




class Empty
{
};

class NotEmpty
{
public:
    virtual ~NotEmpty();
};

union Union {};

struct bit_zero
{
    int :  0;
};

class Abstract
{
public:
    virtual ~Abstract() = 0;
};

struct A
{
    ~A();
};

namespace boost
{
#if defined(BOOST_CONVERSION_NO_IS_DESTRUCTIBLE)
  template <> struct is_destructible< A >  : true_type {};
  template <> struct is_destructible< Empty >  : true_type {};
  template <> struct is_destructible< Union >  : true_type {};
  template <> struct is_destructible< bit_zero >  : true_type {};
#endif
  template <> struct is_destructible< NotEmpty >  : false_type {};
}

int main()
{
  BOOST_STATIC_ASSERT((! boost::is_destructible<Abstract>::value));
  BOOST_STATIC_ASSERT((! boost::is_destructible<void>::value));
  BOOST_STATIC_ASSERT((! boost::is_destructible<int[]>::value));
  BOOST_STATIC_ASSERT((boost::is_destructible<int&>::value));

  BOOST_STATIC_ASSERT(( boost::is_destructible<A>::value));
  BOOST_STATIC_ASSERT(( boost::is_destructible<bit_zero>::value));
  BOOST_STATIC_ASSERT(( boost::is_destructible<Union>::value));
  BOOST_STATIC_ASSERT(( ! boost::is_destructible<NotEmpty>::value));
  BOOST_STATIC_ASSERT(( boost::is_destructible<Empty>::value));
  BOOST_STATIC_ASSERT(( boost::is_destructible<int>::value));
  BOOST_STATIC_ASSERT(( boost::is_destructible<double>::value));
  BOOST_STATIC_ASSERT(( boost::is_destructible<int*>::value));
  BOOST_STATIC_ASSERT(( boost::is_destructible<const int*>::value));
  BOOST_STATIC_ASSERT(( boost::is_destructible<int[3]>::value));
}



