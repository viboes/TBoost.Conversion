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
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/std/string.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>

using namespace boost;

typedef int A1;
typedef short B1;

void explicit_convert_to() {
  bool b1=true;
  std::string str = boost::convert_to<std::string>(b1);
  bool b2=boost::convert_to<bool>(str);

}
void explicit_assign_to() {
  bool b1=true;
  std::string str;
  boost::assign_to(str, b1);
  bool b2;
  boost::assign_to(b2, str);
}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

