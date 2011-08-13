//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief Defines the any type useful to catch any type on overloadin resolution.
 */

#ifndef BOOST_CONVERSION_TT_DETAIL_ANY_HPP
#define BOOST_CONVERSION_TT_DETAIL_ANY_HPP

namespace boost {
  namespace type_traits {
    namespace detail {
      struct any {
        template <typename T>
        any(T);
      };
    } // detail
  } // type_traits
} // boost

#endif // header

