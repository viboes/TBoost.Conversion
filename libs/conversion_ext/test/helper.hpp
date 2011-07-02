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
#include <boost/conversion/type_traits/is_convertible.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/conversion/type_traits/is_explicitly_convertible.hpp>
#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_extrinsic_convertible.hpp>
#include <boost/conversion/type_traits/is_extrinsic_assignable.hpp>

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE) || defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE) || defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
#define BOOST_CONVERSION_DCL_DEFAULTS(X)                              \
namespace boost                                                       \
{                                                                     \
  template <> struct is_constructible< X >  : true_type {};           \
  template <> struct is_constructible< X, X const& >  : true_type {}; \
template <> struct is_assignable< X&, X const& >  : true_type {};   \
template <> struct is_assignable< X, X >  : true_type {};   \
}
#else
#define BOOST_CONVERSION_DCL_DEFAULTS(X)
#endif

struct A1{};
BOOST_CONVERSION_DCL_DEFAULTS(A1)
struct A2{};
BOOST_CONVERSION_DCL_DEFAULTS(A2)
struct B1{};
BOOST_CONVERSION_DCL_DEFAULTS(B1)
struct B2{};
BOOST_CONVERSION_DCL_DEFAULTS(B2)
    

namespace boost {
    namespace conversion {
        template <>
        struct converter_cp< A1,B1 > : true_type {
            A1 operator()(B1 const &)
            {
                return A1();
            }
        };
        template <>
        struct converter_cp< A2,B2 > : true_type {
            A2 operator()(B2 const &)
            {
                return A2();
            }
        };
          template < >
          struct assigner_cp< A1,B1 > : true_type {
              A1& operator()(A1& to, const B1&)
              {
                  return to;
              }
          };
          template < >
          struct assigner_cp< A2,B2 > : true_type {
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

    BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<B1, A1>::value));
    BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<B2, A2>::value));


    #if defined(BOOST_CONVERSION_ENABLE_CND)
    BOOST_STATIC_ASSERT(( !boost::is_assignable<A1, B1>::value));
    BOOST_STATIC_ASSERT(( !boost::is_assignable<A2, B2>::value));
    BOOST_STATIC_ASSERT(( boost::is_extrinsic_assignable<A1, B1>::value));
    BOOST_STATIC_ASSERT(( boost::is_extrinsic_assignable<A2, B2>::value));
    #endif


#endif //BOOST_CONVERSION_TEST_HELPER__HPP
