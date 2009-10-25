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
#include <boost/conversion/boost/array.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "helper.hpp"

using namespace boost;
using namespace boost::unit_test;

void explicit_convert_to() {
    boost::array<B1,3> bs;
    boost::array<A1,3> as;
    as = convert_to<boost::array<A1,3> >(bs);
    
}
void explicit_assign_to() {
    boost::array<int,3> bs;
    boost::array<short,3> as;
    assign_to(as,bs);
    
    
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("array");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

