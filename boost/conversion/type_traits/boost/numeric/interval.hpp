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
 * @brief Type traits specializations for <boost/array.hpp> types.
 */

#ifndef BOOST_CONVERSION_TT_BOOST_NUMERIC_INTERVAL_HPP
#define BOOST_CONVERSION_TT_BOOST_NUMERIC_INTERVAL_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/numeric/interval.hpp>

namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template < class T, class P>
  struct is_constructible< numeric::interval<T,P> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template < class T, class P>
  struct is_constructible< numeric::interval<T,P>, numeric::interval<T,P> > : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  template < class T, class P>
  struct is_assignable< numeric::interval<T,P>&, numeric::interval<T,P> const& >  : true_type {};
  template < class T, class P>
  struct is_assignable< numeric::interval<T,P>, numeric::interval<T,P> >  : true_type {};
#endif

}

#endif

