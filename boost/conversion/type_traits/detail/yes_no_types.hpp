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
 * @brief Defines the any type useful to catch any type on overload resolution.
 */

#ifndef BOOST_CONVERSION_TT_DETAIL_YES_NO_TYPES_HPP
#define BOOST_CONVERSION_TT_DETAIL_YES_NO_TYPES_HPP

namespace boost {
  namespace type_traits {
    namespace detail {
      //! type useful to compare with the sizeof
      typedef char yes_type;
      //! type useful to compare with the sizeof
      struct no_type { char a[2]; };

    } // detail
  } // type_traits
} // boost

#endif // header

