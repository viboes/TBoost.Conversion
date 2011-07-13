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
 * @brief Type traits specializations for <complex> types.
 */

#ifndef BOOST_CONVERSION_TT_STD_COMPLEX_HPP
#define BOOST_CONVERSION_TT_STD_COMPLEX_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <complex>



namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template < class T >
  struct is_constructible< std::complex<T> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template < class T >
  struct is_constructible< std::complex<T>, std::complex<T> > : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  template < class T >
  struct is_assignable< std::complex<T>, std::complex<T> >  : true_type {};
  template < class T >
  struct is_assignable< std::complex<T>&, std::complex<T> const& >  : true_type {};
#endif

  // These specializations are needed because the std library implementation is not using SFINAE
  template < class Target, class Source>
  struct is_constructible< std::complex<Target>, std::complex<Source> >
    : integral_constant<bool, is_constructible<Target,Source>::value  >
      {};

  template < class Target, class Source>
  struct is_assignable< std::complex<Target>, std::complex<Source> >
      : integral_constant<bool, is_assignable<Target,Source>::value  >
        {};
}

#endif

