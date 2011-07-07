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
#include <boost/assert.hpp>
using namespace boost::conversion;

void try_assign_to_way()
{
  //[FALLBACK_CPP_TRY_ASSIGN_WAY
  std::string str="not an int";
  int t=-1;
  try_assign_to(t,str);
  BOOST_ASSERT(t==-1);
  //]
}

void convert_to_or_fallback_way()
{
  std::string str="not an int";
  //[FALLBACK_CPP_CONVERT_TO_OR_FALLBACK
  short f=-1;
  int t = convert_to_or_fallback<int>(str,f);
  BOOST_ASSERT(t==-1);
  //]
  (void)t;// remove warning: unused variable
}

void convert_to_or_fallback_way_deduced()
{
  std::string str="not an int";
  //[FALLBACK_CPP_CONVERT_TO_OR_FALLBACK_DEDUCED
  int t = convert_to_or_fallback(str,-1);
  BOOST_ASSERT(t==-1);
  //]
  (void)t;// remove warning: unused variable
}

int main()
{

  try_assign_to_way();
  convert_to_or_fallback_way();
  convert_to_or_fallback_way_deduced();

  return 0;
}

//]
