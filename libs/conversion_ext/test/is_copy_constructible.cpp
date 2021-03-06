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
#include <boost/conversion/type_traits/is_copy_constructible.hpp>




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
    A(const A&);
};

#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
namespace boost
{
  template <> struct is_constructible< A, A const& >  : true_type {};
  template <> struct is_constructible< Empty, Empty const& >  : true_type {};
  template <> struct is_constructible< NotEmpty, NotEmpty const& >  : true_type {};
  template <> struct is_constructible< Union, Union const& >  : true_type {};
  template <> struct is_constructible< bit_zero, bit_zero const& >  : true_type {};
}
#endif

int main()
{
  BOOST_STATIC_ASSERT((!boost::is_copy_constructible<Abstract>::value));
  BOOST_STATIC_ASSERT((!boost::is_copy_constructible<void>::value));
  BOOST_STATIC_ASSERT((!boost::is_copy_constructible<int[]>::value));
  BOOST_STATIC_ASSERT((!boost::is_copy_constructible<int[3]>::value));

  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<A>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<int&>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<bit_zero>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<Union>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<NotEmpty>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<Empty>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<int>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<double>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<int*>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_constructible<const int*>::value));
}


