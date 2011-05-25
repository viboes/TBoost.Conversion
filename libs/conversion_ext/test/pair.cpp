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
#include <boost/conversion/std/pair.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include "helper.hpp"

using namespace boost;

void explicit_convert_to() {
    B1 b1;
    B2 b2;
    std::pair<B1,B2> b;
    std::pair<A1,A2> a1(boost::conversion::convert_to<std::pair<A1,A2> >(b));
    std::pair<A1,A2> a2(boost::conversion::convert_to<std::pair<A1,A2> >(std::pair<B1,B2>(b1,b2)));
    std::pair<A1,A2> a3(boost::conversion::convert_to<std::pair<A1,A2> >(std::make_pair(b1,b2)));

}
void explicit_assign_to() {
    B1 b1;
    B2 b2;
    std::pair<A1,A2> a;
    std::pair<B1,B2> b;
    boost::conversion::assign_to(a,b);
    boost::conversion::assign_to(a, std::pair<B1,B2>(b1,b2));
    boost::conversion::assign_to(a, std::make_pair(b1,b2));

}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

