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

using boost::optional;
using namespace boost::conversion;

void try_catch_way()
{
  //[NO_THROW_CPP_TRY_CATCH_WAY
  int t;
  try
  {
    std::string str="not an int";
    t = convert_to<int>(str);
  } catch(...)
  {
    std::cout << " Not an integer" << std::endl;
  }
  //]
}
void try_convert_to_way()
{
  int t;
  std::string str="not an int";
  optional<int> optt =  try_convert_to<int>(str);
  if (!optt)
  {
    std::cout << " Not an integer" << std::endl;
  }
}

void convert_to_optional_way()
{
  int t;
  std::string str="not an int";
  optional<int> optt =  convert_to<optional<int> >(str);
  if (!optt)
  {
    std::cout << " Not an integer" << std::endl;
  }
}

void try_assign_to_way()
{
  int t;
  std::string str="not an int";

  if (!try_assign_to(t,str))
  {
    std::cout << " Not an integer" << std::endl;
  }
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
