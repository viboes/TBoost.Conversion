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
    
#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

namespace boost {
    namespace conversion { namespace overload_workaround {
        template <>
        struct convert_to< A1,B1 > {
            inline static A1 apply(B1 const &)
            {
                return A1();
            }
        };
        template < >
        struct assign_to< A1,B1 > {
            inline static A1& apply(A1& to, const B1&)
            {
                return to;
            }
        };
        template <>
        struct convert_to< A2,B2 > {
            inline static A2 apply(B2 const &)
            {
                return A2();
            }
        };
        template < >
        struct assign_to< A2,B2 > {
            inline static A2& apply(A2& to, const B2&)
            {
                return to;
            }
        };
    }
}
#else
    A1 convert_to(const B1&, boost::dummy::type_tag<A1> const&) {
        return A1();
    }

    A1& assign_to(A1& to, const B1&, boost::dummy::type_tag<A1> const&) {
        return to;
    }
    A2 convert_to(const B2&, boost::dummy::type_tag<A2> const&) {
        return A2();
    }

    A2& assign_to(A2& to, const B2&, boost::dummy::type_tag<A2> const&) {
        return to;
    }

#endif
#endif //BOOST_CONVERSION_TEST_HELPER__HPP
