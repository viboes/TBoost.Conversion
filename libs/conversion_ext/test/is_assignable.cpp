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
#if 0
B b;
A a;
typedef char yes_type;
struct no_type { char _[2]; };
template<std::size_t N>
struct dummy{};

//BOOST_STATIC_ASSERT(( sizeof((a = b))>0 ));
BOOST_STATIC_ASSERT(( sizeof((b = boost::declval<A>()))>0 ));

dummy<sizeof(b = boost::declval<A>())> ptr;

yes_type
test(dummy<sizeof((b = boost::declval<A>()))>*);

static no_type
test(...);
static const bool value = sizeof(test(0)) == sizeof(yes_type);
BOOST_STATIC_ASSERT(( value ));
#endif

int main()
{

//  std:: cout << sizeof((b = a)) << std::endl;
//  std:: cout << sizeof((b = boost::declval<A>())) << std::endl;

  BOOST_STATIC_ASSERT(( boost::is_assignable<int&, int&>::value));
  BOOST_STATIC_ASSERT(( boost::is_assignable<int&, int>::value));
  BOOST_STATIC_ASSERT((!boost::is_assignable<int, int&>::value));
  BOOST_STATIC_ASSERT(( boost::is_assignable<int&, double>::value));
  BOOST_STATIC_ASSERT(( boost::is_assignable<B, A>::value));
  BOOST_STATIC_ASSERT((!boost::is_assignable<A, B>::value));

  return 0;
}


