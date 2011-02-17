//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <complex>
#include <boost/conversion/std/complex.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include "helper.hpp"

using namespace boost;

void explicit_convert_to() {
    B1 b1;
    B1 b2;
    std::complex<B1> b;
    std::complex<A1> a1(boost::convert_to<std::complex<A1> >(b));
    std::complex<A1> a2(boost::convert_to<std::complex<A1> >(std::complex<B1>(b1,b2)));

}
void explicit_assign_to() {
    B1 b1;
    B1 b2;
    std::complex<A1> a;
    std::complex<B1> b;
    boost::assign_to(a,b);
    boost::assign_to(a,std::complex<B1>(b1,b2));
}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

