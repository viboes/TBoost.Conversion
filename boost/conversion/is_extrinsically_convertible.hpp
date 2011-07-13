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
 * @brief Defines the type trait @c is_extrinsically_convertible.
 */

#ifndef BOOST_CONVERSION_IS_EXTRINSIC_CONVERTIBLE_HPP
#define BOOST_CONVERSION_IS_EXTRINSIC_CONVERTIBLE_HPP

#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/fusion/tuple.hpp>

namespace boost {
  namespace conversion {

  /**
   * States if @c Source is extrinsically convertible to @c Target.
   *
   * Condition: @c true_type if and only if the return expression in the following code
   * would be well-formed:
   * @code
   *   Target test() { return implicit_convert_to<Target>(declval<Source>()); }
   * @endcode
   *
   * @Requires @c Target and @c Source must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
   *
   */
  template <class Source, class Target>
  struct is_extrinsically_convertible : conversion::converter<
    Target, Source
    //typename remove_reference<typename remove_cv<Target>::type>::type,
    //typename remove_reference<typename remove_cv<Source>::type>::type
    > {};
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  template <class T>
  struct is_extrinsically_convertible<fusion::void_,T> : false_type {};
  template <>
  struct is_extrinsically_convertible<void, void> : true_type {};
  template <>
  struct is_extrinsically_convertible<const void,void> : true_type {};
  template <>
  struct is_extrinsically_convertible<void, const void> : true_type {};
  template <>
  struct is_extrinsically_convertible<const void, const void> : true_type {};
#endif

  }
}


#endif

