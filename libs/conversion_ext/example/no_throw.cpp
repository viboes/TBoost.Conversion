//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[NO_THROW_CPP

#include <boost/conversion/include.hpp>
#include <boost/conversion/std/string.hpp>
#include <iostream>
#include <boost/assert.hpp>

using boost::optional;
using namespace boost::conversion;

void try_catch_way()
{
  //[NO_THROW_CPP_TRY_CATCH_WAY
  std::string str="not an int";
  int t;
  try {
    t = convert_to<int>(str);
    BOOST_ASSERT(false);
  } catch(...)   {
    std::cout << " Not an integer" << std::endl;
  }
  //]
}
void try_convert_to_way()
{
  std::string str="not an int";
  //[NO_THROW_CPP_TRY_CONVERT_WAY
  optional<int> optt =  try_convert_to<int>(str);
  if (!optt)
  {
    std::cout << " Not an integer" << std::endl;
    BOOST_ASSERT(true);
  }
  //]
}

void convert_to_optional_way()
{
  std::string str="not an int";
  //[NO_THROW_CPP_TRY_CONVERT_TO_OPT_WAY
  optional<int> optt =  convert_to<optional<int> >(str);
  if (!optt)
  {
    std::cout << " Not an integer" << std::endl;
    BOOST_ASSERT(true);
  }
  //]
}

void try_assign_to_way()
{
  std::string str="not an int";
  int t;
  //[NO_THROW_CPP_TRY_ASSIGN_WAY
  if (!try_assign_to(t,str))
  {
    std::cout << " Not an integer" << std::endl;
    BOOST_ASSERT(true);
  }
  //]
}

int main()
{
  try_catch_way();
  try_convert_to_way();
  convert_to_optional_way();
  try_assign_to_way();

  return 0;
}

//]
