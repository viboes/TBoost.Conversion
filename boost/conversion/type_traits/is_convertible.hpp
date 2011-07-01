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

  template < >
  struct is_convertible< const void,  void>  : true_type  {};
  template < >
  struct is_convertible<  void,  const void>  : true_type  {};

  template < class Target, class Source, std::size_t N>
  struct is_convertible< Target[N], Source[N] >: false_type  {};
  template < class Target, class Source, std::size_t N>
  struct is_convertible< const Target[N], const Source[N] >: false_type  {};


  template <class A1, class A2, class B1, class B2>
  struct is_convertible< std::pair<A1,A2>, std::pair<B1,B2> >
      : integral_constant<bool, is_convertible<A1,B1>::value && is_convertible<A2,B2>::value >
        {};

#if 0
  template <class T1, class T2, std::size_t N>
  struct is_convertible< boost::array<T1,N>, boost::array<T2,N> >
      : integral_constant<bool, is_convertible<T1,T2>::value  >
        {};
#endif
  template < class Target, class Source>
  struct is_convertible< std::complex<Target>, std::complex<Source> >
      : integral_constant<bool, is_convertible<Target,Source>::value  >
        {};

  template < class T1, class A1, class T2, class A2>
  struct is_convertible< std::vector<T1,A1>, std::vector<T2,A2> >
      : integral_constant<bool, is_convertible<T1,T2>::value  >
        {};

  template <class A1, class A2, class B1, class B2>
  struct is_convertible< fusion::tuple<A1,A2>, fusion::tuple<B1,B2> >
      : integral_constant<bool, is_convertible<A1,B1>::value && is_convertible<A2,B2>::value >
        {};

  template <class A1, class A2, class A3, class B1, class B2, class B3>
  struct is_convertible< fusion::tuple<A1,A2,A3>, fusion::tuple<B1,B2,B3> >
      : integral_constant<bool, is_convertible<A1,B1>::value && is_convertible<A2,B2>::value&& is_convertible<A3,B3>::value >
        {};

}

#endif

