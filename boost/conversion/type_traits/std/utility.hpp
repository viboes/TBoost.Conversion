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
 * @brief Type traits specializations for <utility> classes.
 */

#ifndef BOOST_CONVERSION_TT_UTILITY_HPP
#define BOOST_CONVERSION_TT_UTILITY_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <utility>



namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  //! Specialization for std::pair<T,U> default constructor
  template < class T, class U>
  struct is_constructible< std::pair<T,U> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  //! Specialization for std::pair<T,U> default copy constructor
  template < class T, class U>
  struct is_constructible< std::pair<T,U>, std::pair<T,U> const& >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  //! Specialization for std::pair<T,U> assignment operator
  template < class T, class U>
  struct is_assignable< std::pair<T,U>, std::pair<T,U> >  : true_type {};
  //! Specialization for std::pair<T,U> assignment operator
  template < class T, class U>
  struct is_assignable< std::pair<T,U>&, std::pair<T,U> const& >  : true_type {};
#endif

  // these specializations are needed because the libraries define the assignment operator without using SFINAE
  template <class A1, class A2, class B1, class B2>
  struct is_constructible< std::pair<A1,A2>, std::pair<B1,B2> >
    : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value >
      {};

  template <class A1, class A2, class B1, class B2>
  struct is_assignable< std::pair<A1,A2>, std::pair<B1,B2> >
      : integral_constant<bool, is_assignable<A1,B1>::value && is_assignable<A2,B2>::value >
        {};
}

#endif

