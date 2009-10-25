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
#include <boost/conversion/boost/interval.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace boost::unit_test;

typedef int A1;
typedef short B1;

void explicit_convert_to() {
    B1 b1;
    B1 b2;
    numeric::interval<B1> b;
    numeric::interval<A1> a1(convert_to<numeric::interval<A1> >(b));
    numeric::interval<A1> a2(convert_to<numeric::interval<A1> >(numeric::interval<B1>(b1,b2)));
    
}
void explicit_assign_to() {
    B1 b1;
    B1 b2;
    numeric::interval<A1> a;
    numeric::interval<B1> b;
    assign_to(a,b);
    assign_to(a,numeric::interval<B1>(b1,b2));
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("interval");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

