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
 * @brief
 */


#ifndef BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_EXTRINSIC_CONVERTIBLE_HPP

#include <boost/conversion/explicit_convert_to.hpp>
#include <boost/fusion/tuple.hpp>

namespace boost {

  template <class Source, class Target>
  struct is_extrinsic_explicit_convertible : conversion::explicit_converter<Target, Source> {};
  template <class T>
  struct is_extrinsic_explicit_convertible<fusion::void_,T> : false_type {};
  template <>
  struct is_extrinsic_explicit_convertible<void, void> : true_type {};
  template <>
  struct is_extrinsic_explicit_convertible<const void,void> : true_type {};
  template <>
  struct is_extrinsic_explicit_convertible<void, const void> : true_type {};
  template <>
  struct is_extrinsic_explicit_convertible<const void, const void> : true_type {};

}


#endif

