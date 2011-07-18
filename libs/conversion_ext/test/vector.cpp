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
#include <boost/conversion/std/vector.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include "helper.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;

BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_assignable< A1, B1 >::value));
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_assignable< std::vector<A1>, std::vector<B1> >::value));

void explicit_convert_to() {
    std::vector<B1> vb1;
    {
      std::vector<A1> va1(boost::conversion::convert_to<std::vector<A1> >(vb1));
    }
    std::vector<A1> va1(boost::conversion::implicit_convert_to<std::vector<A1> >(vb1));
    B1 b10, b11, b12, b13;
    std::vector<B1> vb2;
    vb2.reserve(5);
    vb2[0]=b10;
    vb2[1]=b11;
    vb2[2]=b12;
    vb2[3]=b13;
    {
      std::vector<A1> va2(boost::conversion::convert_to<std::vector<A1> >(vb2));
    }
    std::vector<A1> va2(boost::conversion::implicit_convert_to<std::vector<A1> >(vb2));
}
void explicit_assign_to() {
    std::vector<B1> vb1;
    std::vector<A1> va1;
    boost::conversion::assign_to(va1,vb1);

    B1 b10, b11, b12, b13;
    std::vector<B1> vb2;
    vb2.reserve(5);
    vb2[0]=b10;
    vb2[1]=b11;
    vb2[2]=b12;
    vb2[3]=b13;

    boost::conversion::assign_to(va1,vb2);

}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

