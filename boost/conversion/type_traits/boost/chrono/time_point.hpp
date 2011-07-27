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
 * @brief Type traits specializations for <boost/chrono/time_point.hpp> types.
 */

#ifndef BOOST_CONVERSION_TT_BOOST_CHRONO_TIME_POINT_HPP
#define BOOST_CONVERSION_TT_BOOST_CHRONO_TIME_POINT_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/chrono/time_point.hpp>

namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template < class Clock, class Duration>
  struct is_constructible< chrono::time_point<Clock, Duration> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template < class Clock, class Duration>
  struct is_constructible< chrono::time_point<Clock, Duration>, chrono::time_point<Clock, Duration> > : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  template < class Clock, class Duration>
  struct is_assignable< chrono::time_point<Clock, Duration>&, chrono::time_point<Clock, Duration> const& >  : true_type {};
  template < class Clock, class Duration>
  struct is_assignable< chrono::time_point<Clock, Duration>, chrono::time_point<Clock, Duration> >  : true_type {};
#endif

}

#endif

