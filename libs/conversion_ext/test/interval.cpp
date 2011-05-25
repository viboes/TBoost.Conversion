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
#include <boost/conversion/boost/interval.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>

using namespace boost;

typedef int A1;
typedef short B1;

void explicit_convert_to() {
    B1 b1(1);
    B1 b2(3);
    boost::numeric::interval<B1> b(1,5);
    boost::numeric::interval<A1> a1(boost::conversion::convert_to<boost::numeric::interval<A1> >(b));
    boost::numeric::interval<A1> a2(boost::conversion::convert_to<boost::numeric::interval<A1> >(
                boost::numeric::interval<B1>(b1,b2)));

}
void explicit_assign_to() {
    B1 b1(1);
    B1 b2(3);
    boost::numeric::interval<A1> a(1,4);
    boost::numeric::interval<B1> b(1,4);
    boost::conversion::assign_to(a,b);
    boost::conversion::assign_to(a,boost::numeric::interval<B1>(b1,b2));
}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

