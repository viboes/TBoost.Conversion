//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERSION_TEST_HELPER_HPP
#define BOOST_CONVERSION_TEST_HELPER_HPP

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

struct A1{};
struct A2{};
struct B1{};
struct B2{};
    

namespace boost {
    namespace conversion {
        template <>
        struct converter< A1,B1 > {
            A1 operator()(B1 const &)
            {
                return A1();
            }
        };
        template <>
        struct converter< A2,B2 > {
            A2 operator()(B2 const &)
            {
                return A2();
            }
        };
          template < >
          struct assigner< A1,B1 > {
              A1& operator()(A1& to, const B1&)
              {
                  return to;
              }
          };
          template < >
          struct assigner< A2,B2 > {
              A2& operator()(A2& to, const B2&)
              {
                  return to;
              }
          };

    }
}
#if defined(BOOST_CONVERSION_DOUBLE_CP)
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    A1 convert_to(const B1&, boost::conversion::dummy::type_tag<A1> const&) {
        return A1();
    }

    A1& assign_to(A1& to, const B1&) {
        return to;
    }
    A2 convert_to(const B2&, boost::conversion::dummy::type_tag<A2> const&) {
        return A2();
    }

    A2& assign_to(A2& to, const B2&) {
        return to;
    }

#endif
#endif
#endif //BOOST_CONVERSION_TEST_HELPER__HPP
