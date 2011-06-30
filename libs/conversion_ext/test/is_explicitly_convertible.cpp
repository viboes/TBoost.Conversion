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
#include <boost/conversion/type_traits/is_explicitly_convertible.hpp>

struct A
{
    explicit A(int);
    A(double);
    A(int, double);
    A(A const&);
};

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
  BOOST_STATIC_ASSERT((boost::is_explicitly_convertible<const int, int>::value));
  BOOST_STATIC_ASSERT((boost::is_explicitly_convertible<int, A>::value));
  BOOST_STATIC_ASSERT((boost::is_explicitly_convertible<double, A>::value));
  BOOST_STATIC_ASSERT((!boost::is_explicitly_convertible<void,A>::value));
}
