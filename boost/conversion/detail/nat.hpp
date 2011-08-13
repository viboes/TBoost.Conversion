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
 * @brief Defines the nat type used as default of variadic templates to mean not a type.
 */

#ifndef BOOST_CONVERSION_DETAIL_NAT_HPP
#define BOOST_CONVERSION_DETAIL_NAT_HPP

namespace boost {
  namespace conversion {
    namespace detail {
    //! not a type. used as default of variadic templates
    struct nat {};

  } // detail
} // conversion
} // boost

#endif // header

