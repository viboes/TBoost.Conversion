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
#include <boost/conversion/std/complex.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace boost::unit_test;

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
  A1& assign_to<A1,B1>(const B1& from, A1& to) {
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
            inline static A2& apply(const B2& from, A2& to)
            {
                return to;
            }
        };
    }


}    
void explicit_convert_to() {
    B1 b1;
    B1 b2;
    std::complex<B1> b;
    std::complex<A1> a1(convert_to<std::complex<A1> >(b));
    std::complex<A1> a2(convert_to<std::complex<A1> >(std::complex<B1>(b1,b2)));
    
}
void explicit_assign_to() {
    B1 b1;
    B1 b2;
    std::complex<A1> a;
    std::complex<B1> b;
    assign_to(b,a);
    assign_to(std::complex<B1>(b1,b2),a);
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("complex");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

