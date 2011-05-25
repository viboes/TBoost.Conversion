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
#include <boost/conversion/boost/optional.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>

using namespace boost;

struct A1{};
struct B1{};
A1 convert_to(const B1&, boost::dummy::type_tag<A1> const&) 
{
  return A1();
}

A1& assign_to(A1& to, const B1&) 
{
  return to;
}


void explicit_convert_to() 
{
  B1 b1;
  boost::optional<B1> b;
  boost::optional<A1> a1(boost::conversion::convert_to<boost::optional<A1> >(b));
  optional<A1> a3;
  a3=conversion::convert_to<optional<A1> >(b);
  a3=conversion::convert_to<optional<A1> >(b1);
  boost::optional<A1> a2(boost::conversion::convert_to<boost::optional<A1> >(boost::optional<B1>(b1)));
  
}

void explicit_assign_to() 
{
  B1 b1;
  boost::optional<A1> a;
  boost::optional<B1> b;
  //assign_to(b,a);
  boost::conversion::assign_to(a, boost::optional<B1>(b1));
}

int main()
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

