//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/std/string.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/conversion/is_extrinsically_convertible.hpp>
#include <boost/conversion/is_extrinsically_assignable.hpp>


using namespace boost;

typedef int A1;
typedef short B1;


BOOST_STATIC_ASSERT(( boost::is_copy_assignable<bool >::value));
BOOST_STATIC_ASSERT(( boost::is_copy_assignable<std::string >::value));
BOOST_STATIC_ASSERT(( !boost::is_assignable<std::string, bool >::value));
BOOST_STATIC_ASSERT(( !boost::is_assignable<bool, std::string >::value));
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<std::string, bool >::value));
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<bool, std::string>::value));
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_assignable<std::string, bool >::value));
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_assignable<bool, std::string >::value));

void explicit_convert_to() {
  bool b1=true;
  std::string str = boost::conversion::convert_to<std::string>(b1);
  bool b2=boost::conversion::convert_to<bool>(str);
  BOOST_TEST(b2);
}
void explicit_assign_to() {
  bool b1=true;
  std::string str;
  boost::conversion::assign_to(str, b1);

  bool b2=false;
  boost::conversion::assign_to(b2, str);
  BOOST_TEST(b2);
}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

