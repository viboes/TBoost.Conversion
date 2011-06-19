//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[FALLBACK_CPP

#include <boost/conversion/include.hpp>
#include <boost/conversion/std/string.hpp>
#include <iostream>
using namespace boost::conversion;

void try_assign_to_way()
{
  std::string str="not an int";
  //[FALLBACK_CPP_TRY_ASSIGN_WAY
  int t=-1;
  try_assign_to(t,str);
  //]
}

void convert_to_or_fallback_way()
{
  std::string str="not an int";
  //[FALLBACK_CPP_CONVERT_TO_OR_FALLBACK
  int t = convert_to_or_fallback<int>(str,-1);
  //]
}

int main()
{

  try_assign_to_way();
  convert_to_or_fallback_way();

  return 0;
}

//]
