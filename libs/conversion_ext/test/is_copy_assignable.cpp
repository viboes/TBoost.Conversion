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
#include <boost/conversion/type_traits/is_copy_assignable.hpp>



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

struct A
{
    A();
};

int main()
{
  BOOST_STATIC_ASSERT(( boost::is_copy_assignable<int>::value));
  //BOOST_STATIC_ASSERT((!boost::is_copy_assignable<const int>::value));
  //BOOST_STATIC_ASSERT((!boost::is_copy_assignable<int[]>::value));
  //BOOST_STATIC_ASSERT((!boost::is_copy_assignable<int[3]>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_assignable<int&>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_assignable<A>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_assignable<bit_zero>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_assignable<Union>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_assignable<NotEmpty>::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_assignable<Empty>::value));
}





