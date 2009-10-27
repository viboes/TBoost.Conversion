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
#include <boost/conversion/boost/tuple.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "helper.hpp"

using namespace boost;
using namespace boost::unit_test;

void explicit_convert_to() {
    B1 b1;
    B2 b2;
    fusion::tuple<B1,B2> b;
    fusion::tuple<A1,A2> a1(conversion::convert_to<fusion::tuple<A1,A2> >(b));
    fusion::tuple<A1,A2> a2(conversion::convert_to<fusion::tuple<A1,A2> >(fusion::tuple<B1,B2>(b1,b2)));
    fusion::tuple<A1,A2> a3(conversion::convert_to<fusion::tuple<A1,A2> >(fusion::make_tuple(b1,b2)));
    
}
void explicit_assign_to() {
    B1 b1;
    B2 b2;
    fusion::tuple<A1,A2> a;
    fusion::tuple<B1,B2> b;
    conversion::assign_to(a, b);
    conversion::assign_to(a, fusion::tuple<B1,B2>(b1,b2));
    conversion::assign_to(a, fusion::make_tuple(b1,b2));
    
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("tuple");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

