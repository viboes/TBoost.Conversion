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
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace boost::unit_test;

    struct A1{};
    struct B1{};
    A1 convert_to(const B1&, boost::dummy::type_tag<A1> const&) {
        return A1();
    }

    A1& assign_to(A1& to, const B1&) {
        return to;
    }


void explicit_convert_to() {
    B1 b1;
    boost::optional<B1> b;
    boost::optional<A1> a1(boost::convert_to<boost::optional<A1> >(b));
    //optional<A1> a1;
    //a1=convert_to<optional<A1> >(b);
    boost::optional<A1> a2(boost::convert_to<boost::optional<A1> >(boost::optional<B1>(b1)));

}
void explicit_assign_to() {
    B1 b1;
    boost::optional<A1> a;
    boost::optional<B1> b;
    //assign_to(b,a);
    boost::assign_to(a, boost::optional<B1>(b1));
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("optional");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

