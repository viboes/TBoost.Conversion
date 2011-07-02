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
#include <boost/conversion/boost/chrono_posix_time.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>

using namespace boost;


typedef int A1;
typedef short B1;

void explicit_convert_to() {
    boost::chrono::seconds a(3);
#if defined(BOOST_CONVERSION_ENABLE_CND)|| !defined(BOOST_NO_SFINAE_EXPR)
    {
      boost::posix_time::time_duration b(boost::conversion::convert_to<boost::posix_time::time_duration >(a));
      boost::chrono::seconds c(boost::conversion::convert_to<boost::chrono::seconds>(b));
    }
#endif
    boost::posix_time::time_duration b(boost::conversion::implicit_convert_to<boost::posix_time::time_duration >(a));
    boost::chrono::seconds c(boost::conversion::implicit_convert_to<boost::chrono::seconds>(b));
}
void explicit_assign_to() {
    boost::chrono::seconds a(3);
    boost::posix_time::time_duration b;
    boost::conversion::assign_to(b, a);
    boost::chrono::seconds c;
    boost::conversion::assign_to(c, b);
}

int main( )

{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

