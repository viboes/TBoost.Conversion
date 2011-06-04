//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/type_traits for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief
 */


#ifndef BOOST_CONVERSION_TT_IS_ASSIGNABLE_HPP
#define BOOST_CONVERSION_TT_IS_ASSIGNABLE_HPP

#include <boost/type_traits/intrinsics.hpp>
#if !defined(BOOST_IS_ASSIGNABLE)
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/utility/declval.hpp>
#include <boost/config.hpp>

#if defined(BOOST_NO_DECLTYPE)
#include <boost/typeof/typeof.hpp>
#endif // defined(BOOST_NO_DECLTYPE)

#endif // !defined(BOOST_IS_ASSIGNABLE)

// should be always the last #include directive
#include <boost/type_traits/detail/bool_trait_def.hpp>

namespace boost {
#ifndef BOOST_IS_ASSIGNABLE

  namespace detail {

    namespace is_assignable {
      template <class Target, class Source>
#if !defined(BOOST_NO_DECLTYPE)
      decltype((declval<Target>() = declval<Source>(), true_type()))
#else
      BOOST_TYPEOF_TPL((declval<Target>() = declval<Source>(), true_type()))
#endif
      test(int);

      template <class, class>
      static false_type test(...);

    template<class T, class U>
    struct impl {
#if !defined(BOOST_NO_DECLTYPE)
    typedef decltype(test<T, U>(0)) type;
#else
    typedef BOOST_TYPEOF_TPL((test<T, U>(0))) type;
#endif
    };

    }
  }
  BOOST_TT_AUX_BOOL_TRAIT_DEF2(is_assignable,To,From,(::boost::detail::is_assignable::impl<To,From>::type::value))
  BOOST_TT_AUX_BOOL_TRAIT_DEF2(is_assignable2,To,From,false)

#else

  BOOST_TT_AUX_BOOL_TRAIT_DEF2(is_assignable,To,From,BOOST_IS_ASSIGNABLE(To,From))

#endif
}

#include <boost/type_traits/detail/bool_trait_undef.hpp>

#endif

