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
 * @brief Defines the type trait @c is_copy_assignable.
 */


#ifndef BOOST_CONVERSION_TT_IS_COPY_ASSIGNABLE_HPP
#define BOOST_CONVERSION_TT_IS_COPY_ASSIGNABLE_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>

namespace boost {

  /**
   * States if @c T is copy assignable.
   *
   * Condition: <c>is_assignable<T&, T const&>::value</c> is @c true.
   *
   * @Requires @c T must be a complete type, (possibly cv-qualified) void, or an array of unknown bound.
   */
  template <typename T>
  struct is_copy_assignable : is_assignable<
    T&,
    T const&
    > {};

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)

  /**
   * @c is_copy_assignable specialization for reference types.
   *
   * Condition: references are always copy assignable.
   */
  template <typename T>
  struct is_copy_assignable<T&> : true_type {};
  template <typename T>
  struct is_copy_assignable<T[]> : false_type {};
  template <typename T, std::size_t N>
  struct is_copy_assignable<T[N]> : false_type {};
  template <>
  struct is_copy_assignable<void> : false_type {};

#endif
}


#endif

