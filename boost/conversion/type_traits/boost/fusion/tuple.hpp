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
 * @brief Type traits specializations for <boost/fusion/tuple.hpp> types.
 */

#ifndef BOOST_CONVERSION_TT_BOOST_TUPLE_HPP
#define BOOST_CONVERSION_TT_BOOST_TUPLE_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/conversion/type_traits/is_explicitly_convertible.hpp>
#include <boost/fusion/tuple.hpp>


namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template < typename T1, typename T2, typename T3 >
  struct is_constructible< fusion::tuple<T1,T2,T3> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template < typename T1, typename T2, typename T3 >
  struct is_constructible< fusion::tuple<T1,T2,T3>, fusion::tuple<T1,T2,T3> > : true_type {};
#endif


  // these specializations are needed because the libraries define the assignment operator without using SFINAE
  // TODO Use PP library to manage with variadic templates
  template <typename A1, typename A2, typename B1, typename B2>
  struct is_constructible< fusion::tuple<A1,A2>, fusion::tuple<B1,B2> >
    : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value >
      {};

  template <typename A1, typename A2, typename A3, typename B1, typename B2, typename B3>
  struct is_constructible< fusion::tuple<A1,A2,A3>, fusion::tuple<B1,B2,B3> >
    : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value&& is_constructible<A3,B3>::value >
      {};

  template <typename A1, typename A2, typename B1, typename B2>
  struct is_explicitly_convertible< fusion::tuple<A1,A2>, fusion::tuple<B1,B2> >
    : integral_constant<bool, is_explicitly_convertible<A1,B1>::value && is_explicitly_convertible<A2,B2>::value >
      {};

  template <typename A1, typename A2, typename A3, typename B1, typename B2, typename B3>
  struct is_explicitly_convertible< fusion::tuple<A1,A2,A3>, fusion::tuple<B1,B2,B3> >
    : integral_constant<bool, is_explicitly_convertible<A1,B1>::value && is_explicitly_convertible<A2,B2>::value&& is_explicitly_convertible<A3,B3>::value >
      {};

  template <typename A1, typename A2, typename B1, typename B2>
  struct is_assignable< fusion::tuple<A1,A2>, fusion::tuple<B1,B2> >
      : integral_constant<bool, is_assignable<A1,B1>::value && is_assignable<A2,B2>::value >
        {};

  template <typename A1, typename A2, typename B1, typename B2>
  struct is_assignable< fusion::tuple<A1,A2>&, fusion::tuple<B1,B2> const&>
  : integral_constant<bool, is_assignable<A1,B1>::value && is_assignable<A2,B2>::value >
  {};

  template <typename A1, typename A2, typename A3, typename B1, typename B2, typename B3>
  struct is_assignable< fusion::tuple<A1,A2,A3>, fusion::tuple<B1,B2,B3> >
    : integral_constant<bool, is_assignable<A1,B1>::value && is_assignable<A2,B2>::value&& is_assignable<A3,B3>::value >
      {};
}

#endif

