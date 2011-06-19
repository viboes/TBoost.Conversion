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
    chrono::system_clock::time_point a=chrono::system_clock::now();
#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)
    {
      posix_time::ptime b(boost::conversion::convert_to<posix_time::ptime >(a));
      chrono::system_clock::time_point c(boost::conversion::convert_to<chrono::system_clock::time_point>(b));
    }
#endif
    posix_time::ptime b(boost::conversion::implicit_convert_to<posix_time::ptime >(a));
    chrono::system_clock::time_point c(boost::conversion::implicit_convert_to<chrono::system_clock::time_point>(b));

}
void explicit_assign_to() {
    chrono::system_clock::time_point a=chrono::system_clock::now();
    posix_time::ptime b;
    boost::conversion::assign_to(b, a);
    chrono::system_clock::time_point c;
    boost::conversion::assign_to(c, b);
}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

