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
 * @brief Type traits specializations for <boost/array.hpp> types.
 */

#ifndef BOOST_CONVERSION_TT_BOOST_ARRAY_HPP
#define BOOST_CONVERSION_TT_BOOST_ARRAY_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/array.hpp>

namespace boost {

  // These specializations are needed because the std library implementation is not using SFINAE

  template <class T1, class T2, std::size_t N>
  struct is_assignable< boost::array<T1,N>, boost::array<T2,N> >
      : integral_constant<bool, is_assignable<T1,T2>::value  >
        {};
}

#endif

