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
 * @brief Defines the type trait @c is_move_assignable.
 */


#ifndef BOOST_CONVERSION_TT_IS_MOVE_ASSIGNABLE_HPP
#define BOOST_CONVERSION_TT_IS_MOVE_ASSIGNABLE_HPP
#include <boost/conversion/type_traits/detail/any.hpp>
#include <boost/conversion/type_traits/detail/yes_no_types.hpp>
#include <boost/conversion/type_traits/detail/dummy_size.hpp>

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_copy_assignable.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>

#if ! defined BOOST_NO_RVALUE_REFERENCES
  #if defined _MSC_VER
  #elif defined __clang__
      #define BOOST_CONVERSION_TT_IS_MOVE_ASSIGNABLE_USES_RVALUE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
     #else
      #define BOOST_CONVERSION_TT_IS_MOVE_ASSIGNABLE_USES_RVALUE
     #endif
  #else
      #define BOOST_CONVERSION_TT_IS_MOVE_ASSIGNABLE_USES_RVALUE
  #endif
#else
#endif


namespace boost {

  /**
   * States if @c T is move assignable.
   *
   * Condition: <c>is_assignable<T&, T&&>::value</c> is @c true.
   *
   * @Requires @c T must be a complete type, (possibly cv-qualified) void, or an array of unknown bound.
   */
  template <typename T>
  struct is_move_assignable :
#if defined BOOST_CONVERSION_TT_IS_MOVE_ASSIGNABLE_USES_RVALUE
    is_assignable<T&, T&&>
#else
    is_copy_assignable<T>
#endif
    {};

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)

  /**
   * @c is_copy_assignable specialization for reference types.
   *
   * Condition: references are always copy assignable.
   */
//  template <typename T>
//  struct is_move_assignable<T&> : true_type {};
  template <typename A>
  struct is_move_assignable<A[]> : false_type {};
  template <>
  struct is_move_assignable<void> : false_type {};

#endif
}


#endif

