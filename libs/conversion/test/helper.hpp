//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERSION_TEST_HELPER__HPP
#define BOOST_CONVERSION_TEST_HELPER__HPP

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

struct A1{};
struct A2{};
struct B1{};
struct B2{};

namespace boost { 
    template <>
    A1 convert_to<A1,B1>(const B1& val, type_tag<A1>) {
        return A1();
    }

    template <>
    A1& assign_to<A1,B1>(A1& to, const B1& from) {
        return to;
    }
  
    namespace conversion { namespace partial_specialization_workaround {
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
    }}
}

#endif //BOOST_CONVERSION_TEST_HELPER__HPP
