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
 * @brief Include this file to workaround some failures on the Boost.TypeTraits @c is_convertible.
 */


#ifndef BOOST_CONVERSION_TT_IS_CONVERTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_CONVERTIBLE_HPP

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <utility>
#include <boost/array.hpp>
#include <complex>
#include <vector>
#include <boost/fusion/tuple.hpp>

namespace boost
{

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  template < >
  struct is_convertible< const void,  void>  : true_type  {};
  template < >
  struct is_convertible<  void,  const void>  : true_type  {};

  template < typename Target, typename Source, std::size_t N>
  struct is_convertible< Target[N], Source[N] >: false_type  {};
  template < typename Target, typename Source, std::size_t N>
  struct is_convertible< const Target[N], const Source[N] >: false_type  {};


  template <typename A1, typename A2, typename B1, typename B2>
  struct is_convertible< std::pair<A1,A2>, std::pair<B1,B2> >
      : integral_constant<bool, is_convertible<A1,B1>::value && is_convertible<A2,B2>::value >
        {};

#if 0
  template <typename T1, typename T2, std::size_t N>
  struct is_convertible< boost::array<T1,N>, boost::array<T2,N> >
      : integral_constant<bool, is_convertible<T1,T2>::value  >
        {};
#endif
  template < typename Target, typename Source>
  struct is_convertible< std::complex<Target>, std::complex<Source> >
      : integral_constant<bool, is_convertible<Target,Source>::value  >
        {};

  template < typename T1, typename A1, typename T2, typename A2>
  struct is_convertible< std::vector<T1,A1>, std::vector<T2,A2> >
      : integral_constant<bool, is_convertible<T1,T2>::value  >
        {};

  template <typename A1, typename A2, typename B1, typename B2>
  struct is_convertible< fusion::tuple<A1,A2>, fusion::tuple<B1,B2> >
      : integral_constant<bool, is_convertible<A1,B1>::value && is_convertible<A2,B2>::value >
        {};

  template <typename A1, typename A2, typename A3, typename B1, typename B2, typename B3>
  struct is_convertible< fusion::tuple<A1,A2,A3>, fusion::tuple<B1,B2,B3> >
      : integral_constant<bool, is_convertible<A1,B1>::value && is_convertible<A2,B2>::value&& is_convertible<A3,B3>::value >
        {};

#endif
}

#endif

