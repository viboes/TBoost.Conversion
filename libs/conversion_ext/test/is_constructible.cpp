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
#include <boost/conversion/type_traits/is_constructible.hpp>

struct A
{
    explicit A(int);
    A(double);
    A(int, double);
    A(A const&);
};

struct B
{
};

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
namespace boost
{
  template <> struct is_constructible< B>  : true_type {};
}
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
namespace boost
{
  template <> struct is_constructible< A, int >  : true_type {};
  template <> struct is_constructible< A, double >  : true_type {};
  template <> struct is_constructible< A, int, double >  : true_type {};
  template <> struct is_constructible< A, A const& >  : true_type {};
}
#endif

int main()
{
  // BUG: Default constructible doesn't works yet
  BOOST_STATIC_ASSERT((boost::is_constructible<int>::value));
  BOOST_STATIC_ASSERT((!boost::is_constructible<A>::value));
  BOOST_STATIC_ASSERT((boost::is_constructible<int, const int>::value));
  BOOST_STATIC_ASSERT((boost::is_constructible<A, int>::value));
  BOOST_STATIC_ASSERT((boost::is_constructible<A, double>::value));
  BOOST_STATIC_ASSERT((boost::is_constructible<A, int, double>::value));
  BOOST_STATIC_ASSERT((boost::is_constructible<A, A const&>::value));
  BOOST_STATIC_ASSERT((!boost::is_constructible<void>::value));
  // BUG: We need to add specializations for void
  BOOST_STATIC_ASSERT((!boost::is_constructible<void,A>::value));
  BOOST_STATIC_ASSERT((boost::is_constructible<B>::value));
}
