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
 * @brief Type traits specializations for <vector> types.
 */

#ifndef BOOST_CONVERSION_TT_VECTOR_HPP
#define BOOST_CONVERSION_TT_VECTOR_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <vector>


namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template < class T, class A>
  struct is_constructible< std::vector<T,A> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template < class T, class A>
  struct is_constructible< std::vector<T,A>, std::vector<T,A> > : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  template < class T, class A>
  struct is_assignable< std::vector<T,A>&, std::vector<T,A> const& >  : true_type {};
  template < class T, class A>
  struct is_assignable< std::vector<T,A>, std::vector<T,A> >  : true_type {};
#endif

  // these specializations are needed because the libraries define the assignment operator without using SFINAE

  template < class T1, class A1, class T2, class A2>
  struct is_constructible< std::vector<T1,A1>, std::vector<T2,A2> >
    : integral_constant<bool, is_constructible<T1,T2>::value  >
      {};

  template < class T1, class A1, class T2, class A2>
  struct is_assignable< std::vector<T1,A1>, std::vector<T2,A2> >
      : integral_constant<bool, is_assignable<T1,T2>::value  >
        {};
}

#endif

