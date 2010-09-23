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
#include <boost/conversion/ca_wrapper.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace boost::unit_test;

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
test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("extrinsec");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

