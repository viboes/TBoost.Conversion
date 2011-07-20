//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/boost/optional.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include <boost/conversion/try_convert_to.hpp>
#include <boost/conversion/try_assign_to.hpp>

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE) || defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE) || defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
#define BOOST_CONVERSION_DCL_DEFAULTS(X)                              \
namespace boost                                                       \
{                                                                     \
template <> struct is_constructible< X >  : true_type {};           \
template <> struct is_constructible< X, X const& >  : true_type {}; \
template <> struct is_assignable< X&, X const& >  : true_type {};   \
}
#else
#define BOOST_CONVERSION_DCL_DEFAULTS(X)
#endif


#if defined(BOOST_CONVERSION_DOUBLE_CP2)
struct A1{};
struct B1{};
struct C1{};
A1 convert_to(const B1&, boost::conversion::dummy::type_tag<A1> const&)
{
  return A1();
}
A1 convert_to(const C1&, boost::conversion::dummy::type_tag<A1> const&)
{
  throw 1;
}

A1& assign_to(A1& to, const B1&) 
{
  return to;
}
#else
struct B1{};
BOOST_CONVERSION_DCL_DEFAULTS(B1)
struct C1{};
BOOST_CONVERSION_DCL_DEFAULTS(C1)
struct A1{
  A1() {}
  A1(A1 const&) {}
  A1(B1 const&) {}
  A1(C1 const&) {
    throw 1;
  }
};
BOOST_CONVERSION_DCL_DEFAULTS(A1)

#endif

void explicit_convert_to() 
{
  {
    B1 b1;
    boost::optional<B1> b=b1;
    {
      boost::optional<A1> a(boost::conversion::convert_to<boost::optional<A1> >(b));
      BOOST_TEST(a);
    }
    boost::optional<A1> a(boost::conversion::implicit_convert_to<boost::optional<A1> >(b));
    BOOST_TEST(a);
  }

  {
    B1 b1;
    {
      boost::optional<A1> a(boost::conversion::convert_to<boost::optional<A1> >(boost::optional<B1>(b1)));
      BOOST_TEST(a);
    }
    boost::optional<A1> a(boost::conversion::implicit_convert_to<boost::optional<A1> >(boost::optional<B1>(b1)));
    BOOST_TEST(a);
  }

  { // target is not assigned when the source is not initialized
    boost::optional<B1> b;
    boost::optional<A1> a;
    {
      a=boost::conversion::convert_to<boost::optional<A1> >(b);
      BOOST_TEST(!a);
    }
    a=boost::conversion::implicit_convert_to<boost::optional<A1> >(b);
    BOOST_TEST(!a);
  }

  { // target is not assigned when the source is not initialized
    boost::optional<C1> c;
    boost::optional<A1> a;
    {
      a=boost::conversion::convert_to<boost::optional<A1> >(c);
      BOOST_TEST(!a);
    }
    a=boost::conversion::implicit_convert_to<boost::optional<A1> >(c);
    BOOST_TEST(!a);
  }

  { // conversion of optional throws if conversion of elements throw
    C1 c1;
    boost::optional<C1> c=c1;
    boost::optional<A1> a;
    try {
      {
        a=boost::conversion::convert_to<boost::optional<A1> >(c);
        BOOST_TEST(false);
      }
      a=boost::conversion::implicit_convert_to<boost::optional<A1> >(c);
      BOOST_TEST(false);
    } catch (...) {  }
  }

  
}

void explicit_assign_to() 
{
  { // target is assigned when the source is initialized
    B1 b1;
    boost::optional<A1> a;
    BOOST_TEST(!a);
    boost::conversion::assign_to(a, boost::optional<B1>(b1));
    BOOST_TEST(a);
  }
#if defined(BOOST_CONVERSION_DOUBLE_CP2)
  { // assign_to can be used when found by ADL
    B1 b1;
    boost::optional<A1> a;
    boost::optional<B1> b=b1;
    assign_to(a,b);
    BOOST_TEST(a);
  }
#endif
}

void explicit_try_convert_to()
{
  { // when the target is optional and the source isn't, the target is assigned
    B1 b1;
    boost::optional<A1> a;
    a=boost::conversion::convert_to<boost::optional<A1> >(b1);
    BOOST_TEST(a);
  }
  { // try_convert_to return an optional initialized when the conversion succeeds
    B1 b1;
    boost::optional<A1> a;
    a=boost::conversion::try_convert_to<A1 >(b1);
    BOOST_TEST(a);
  }
  { // try_convert_to return an optional uninitialized when the conversion fails
    C1 c1;
    boost::optional<A1> a;
    a=boost::conversion::try_convert_to<A1 >(c1);
    BOOST_TEST(!a);
  }

}
void explicit_try_assign_to()
{
  {
    A1 a1;
    B1 b1;
    bool res = boost::conversion::try_assign_to<A1 >(a1,b1);
    BOOST_TEST(res);
  }
  {
    A1 a1;
    C1 c1;
    bool res = boost::conversion::try_assign_to<A1 >(a1,c1);
    BOOST_TEST(!res);
  }
}
int main()
{
  explicit_convert_to();
  explicit_assign_to();
  explicit_try_convert_to();
  explicit_try_assign_to();
  return boost::report_errors();
}

