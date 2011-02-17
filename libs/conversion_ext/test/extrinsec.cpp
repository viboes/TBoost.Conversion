//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/ca_wrapper.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>

using namespace boost;

struct A{};
struct B{};

  A convert_to(const B&, boost::dummy::type_tag<A> const&) {
    return A();
  }

  A& assign_to(A& to, const B&, boost::dummy::type_tag<A> const&) {
    return to;
  }


void explicit_convert_to() {
    B b;
    A a(boost::convert_to<A>(b));

}
void explicit_assign_to() {
    B b;
    A a;
    boost::assign_to(a, b);
    boost::mca(a)= b;

}
int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

