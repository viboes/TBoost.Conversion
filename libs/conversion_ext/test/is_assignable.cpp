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
#include <boost/conversion/type_traits/is_assignable.hpp>

struct A
{
};

struct B
{
    B& operator=(A);
};

#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)

namespace boost {
  // these specialization are needed because the compiler doesn't support SFINAE on expression
  template <> struct is_assignable< B, A > : true_type  {};
}

#endif

int main()
{

  BOOST_STATIC_ASSERT(( boost::is_assignable<int&, int&>::value));
  BOOST_STATIC_ASSERT(( boost::is_assignable<int&, int>::value));
  // BUG BOOST_STATIC_ASSERT((!boost::is_assignable<int, int>::value));
  // BUG BOOST_STATIC_ASSERT((!boost::is_assignable<int, int&>::value));
  BOOST_STATIC_ASSERT(( boost::is_assignable<int&, double>::value));
  BOOST_STATIC_ASSERT(( boost::is_assignable<B, A>::value));
  BOOST_STATIC_ASSERT((!boost::is_assignable<A, B>::value));

  return 0;
}


