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
 * @brief Defines the type trait @c is_default_constructible.
 */


#ifndef BOOST_CONVERSION_TT_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost {

  /**
   * States if @c T is default constructible.
   *
   * Condition: <c>is_constructible<T>::value</c> is @c true.
   *
   * @Requires @c T must be a complete type, (possibly cv-qualified) void, or an array of unknown bound.
   */
  template <class T>
  struct is_default_constructible : is_constructible<
    T
    > {};

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
//  template <>
//  struct is_default_constructible<void> : false_type {};
  template <typename T>
  struct is_default_constructible<T&> : false_type {};
//  template <typename T>
//  struct is_default_constructible<T[]> : false_type {};
  template <typename T, std::size_t N>
  struct is_default_constructible<T[N]> : true_type {};
#endif

}


#endif

