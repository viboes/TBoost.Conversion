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
 * @brief Defines the dummy_size useful to to accept a sizeof as parameter.
 */

#ifndef BOOST_CONVERSION_TT_DETAIL_DUMMY_SIZE_HPP
#define BOOST_CONVERSION_TT_DETAIL_DUMMY_SIZE_HPP

namespace boost {
  namespace type_traits {
    namespace detail {
      //! type useful to accept a sizeof as parameter
      template <std::size_t N>
      struct dummy_size;

    } // detail
  } // type_traits
} // boost

#endif // header

