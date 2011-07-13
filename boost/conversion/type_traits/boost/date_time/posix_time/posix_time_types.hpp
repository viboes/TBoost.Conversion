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
 * @brief Type traits specializations for <boost/date_time/posix_time/posix_time_types.hpp> types.
 */

#ifndef BOOST_CONVERSION_TT_BOOST_DATE_TIME_POSIX_TIME_HPP
#define BOOST_CONVERSION_TT_BOOST_DATE_TIME_POSIX_TIME_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template <> struct is_constructible< posix_time::time_duration >  : true_type {};
  template <> struct is_constructible< boost::posix_time::ptime >  : true_type {};
#endif

#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template <> struct is_constructible< posix_time::time_duration, posix_time::time_duration const& >  : true_type {};
  template <> struct is_constructible< boost::posix_time::ptime, boost::posix_time::ptime const& >  : true_type {};
#endif

#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  template <> struct is_assignable< posix_time::time_duration&, posix_time::time_duration const& >  : true_type {};
  template <> struct is_assignable< posix_time::time_duration, posix_time::time_duration >  : true_type {};
  template <> struct is_assignable< boost::posix_time::ptime&, boost::posix_time::ptime const& >  : true_type {};
  template <> struct is_assignable< boost::posix_time::ptime, boost::posix_time::ptime >  : true_type {};
#endif





}

#endif

