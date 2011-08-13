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
 * @brief Type traits specializations for <boost/chrono/duration.hpp> types.
 */

#ifndef BOOST_CONVERSION_TT_BOOST_CHRONO_DURATION_HPP
#define BOOST_CONVERSION_TT_BOOST_CHRONO_DURATION_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/chrono/duration.hpp>

namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template < typename Rep, typename Period >
  struct is_constructible< chrono::duration<Rep, Period> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template < typename Rep, typename Period >
  struct is_constructible< chrono::duration<Rep, Period>, chrono::duration<Rep, Period> > : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  template < typename Rep, typename Period >
  struct is_assignable< chrono::duration<Rep, Period>&, chrono::duration<Rep, Period> const& >  : true_type {};
  template < typename Rep, typename Period >
  struct is_assignable< chrono::duration<Rep, Period>, chrono::duration<Rep, Period> >  : true_type {};
#endif


}

#endif

