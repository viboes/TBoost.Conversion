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
struct C{};

void f(B) {}

  A convert_to(const B&, boost::conversion::dummy::type_tag<A> const&) {
    return A();
  }

  A& assign_to(A& to, const B&, boost::conversion::dummy::type_tag<A> const&) {
    return to;
  }

  B convert_to(const C&, boost::conversion::dummy::type_tag<B> const&) {
    return B();
  }

  B& assign_to(B& to, const C&, boost::conversion::dummy::type_tag<B> const&) {
    return to;
  }

void explicit_convert_to() {
    B b;
    A a(boost::conversion::convert_to<A>(b));

}
void explicit_assign_to() {
    B b;
    A a;
    boost::conversion::assign_to(a, b);
    boost::mca(a)= b;

}
void explicit_chain_assign_to() {
    C c;
    B b;
    A a;
    boost::conversion::assign_to(a, boost::conversion::assign_to(b,c));
    boost::mca(a)= boost::mca(b) = c;

}
void implicit_conversion_via_mca() {
    C  c;
    f(mca(c));
}
int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  explicit_chain_assign_to();
  implicit_conversion_via_mca();
  return boost::report_errors();
}

