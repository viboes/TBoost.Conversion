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
#include <boost/conversion/boost/tuple.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "helper.hpp"

using namespace boost;
using namespace boost::unit_test;

#if 0
struct A1{};
struct A2{};
struct B1{};
struct B2{};

namespace boost {
  template <>
  A1 convert_to<A1,B1>(const B1& val) {
    return A1();
  }

  template <>
  A1& assign_to<A1,B1>(A1& to, const B1& from) {
    return to;
  }
    
    namespace partial_specialization_workaround {
        template <>
        struct convert_to< A2,B2 > {
            inline static A2 apply(B2 const & from)
            {
                return A2();
            }
        };
        template < >
        struct assign_to< A2,B2 > {
            inline static A2& apply(A2& to, const B2& from)
            {
                return to;
            }
        };
    }


}    
#endif
void explicit_convert_to() {
    B1 b1;
    B2 b2;
    fusion::tuple<B1,B2> b;
    fusion::tuple<A1,A2> a1(convert_to<fusion::tuple<A1,A2> >(b));
    fusion::tuple<A1,A2> a2(convert_to<fusion::tuple<A1,A2> >(fusion::tuple<B1,B2>(b1,b2)));
    fusion::tuple<A1,A2> a3(convert_to<fusion::tuple<A1,A2> >(fusion::make_tuple(b1,b2)));
    
}
void explicit_assign_to() {
    B1 b1;
    B2 b2;
    fusion::tuple<A1,A2> a;
    fusion::tuple<B1,B2> b;
    assign_to(a, b);
    assign_to(a, fusion::tuple<B1,B2>(b1,b2));
    assign_to(a, fusion::make_tuple(b1,b2));
    
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("tuple");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

