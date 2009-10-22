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
#include <boost/conversion/boost/chrono_posix_time.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace boost::unit_test;

typedef int A1;
typedef short B1;

void explicit_convert_to() {
    chrono::system_clock::time_point a=chrono::system_clock::now();
    posix_time::ptime b(convert_to<posix_time::ptime >(a));
    chrono::system_clock::time_point c(convert_to<chrono::system_clock::time_point>(b));
    
}
void explicit_assign_to() {
    chrono::system_clock::time_point a=chrono::system_clock::now();
    posix_time::ptime b;
    assign_to(b, a);
    chrono::system_clock::time_point c;
    assign_to(c, b);
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("time");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

