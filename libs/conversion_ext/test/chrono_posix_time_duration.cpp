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
    boost::chrono::seconds a(3);
    boost::posix_time::time_duration b(boost::convert_to<boost::posix_time::time_duration >(a));
    boost::chrono::seconds c(boost::convert_to<boost::chrono::seconds>(b));

}
void explicit_assign_to() {
    boost::chrono::seconds a(3);
    boost::posix_time::time_duration b;
    boost::assign_to(b, a);
    boost::chrono::seconds c;
    boost::assign_to(c, b);
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("duration");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

