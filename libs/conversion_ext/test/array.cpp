//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/boost/array.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include "helper.hpp"

using namespace boost;

void explicit_convert_to() {
    boost::array<B1,3> bs;
    boost::array<A1,3> as;
    as = boost::convert_to<boost::array<A1,3> >(bs);

}
void explicit_assign_to() {
    boost::array<int,3> bs;
    boost::array<short,3> as;
    boost::assign_to(as,bs);


}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

