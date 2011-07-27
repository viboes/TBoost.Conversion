//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////


/*!
 @file
 @brief
 Include this file when using conversions between @c boost::posix_time::time_duration and @c boost::chrono::duration<>.
 */

#ifndef BOOST_CONVERSION_CHRONO_DURATION_TO_POSIX_TIME_DURATION_HPP
#define BOOST_CONVERSION_CHRONO_DURATION_TO_POSIX_TIME_DURATION_HPP

#include <boost/conversion/type_traits/boost/chrono/duration.hpp>
//#include <boost/chrono/duration.hpp>
#include <boost/conversion/type_traits/boost/date_time/posix_time/posix_time_types.hpp>
//#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>

namespace boost {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  //! trick to generate the doc. Don't take care of it
  struct trick_chrono_duration{};
#endif
//#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
//  template <> struct is_constructible< posix_time::time_duration >  : true_type {};
//#endif
//#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
//  template <> struct is_constructible< posix_time::time_duration, posix_time::time_duration const& >  : true_type {};
//#endif
//#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
//  template <> struct is_assignable< posix_time::time_duration&, posix_time::time_duration const& >  : true_type {};
//  template <> struct is_assignable< posix_time::time_duration, posix_time::time_duration >  : true_type {};
//#endif


//#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
//  template < class Rep, class Period >
//  struct is_constructible< chrono::duration<Rep, Period> >  : true_type {};
//#endif
//#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
//  template < class Rep, class Period >
//  struct is_constructible< chrono::duration<Rep, Period>, chrono::duration<Rep, Period> > : true_type {};
//#endif
//#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
//  template < class Rep, class Period >
//  struct is_assignable< chrono::duration<Rep, Period>&, chrono::duration<Rep, Period> const& >  : true_type {};
//  template < class Rep, class Period >
//  struct is_assignable< chrono::duration<Rep, Period>, chrono::duration<Rep, Period> >  : true_type {};
//#endif
  
  
  namespace conversion {
    //! @brief @c implicit_converter specialization for conversions from @c boost::chrono::duration<> to @c boost::posix_time::time_duration.
    //!
    template < class Rep, class Period>
    struct implicit_converter_cp<posix_time::time_duration, chrono::duration<Rep, Period>
     > : true_type
    {
      //! @Returns the duration converted to seconds+nanoseconds following the boost::posix_time::time_duration formatting.
      posix_time::time_duration operator()(chrono::duration<Rep, Period> const & from)
      {
        typedef chrono::duration<Rep, Period> src_duration_t;
        typedef chrono::nanoseconds duration_t;
        typedef duration_t::rep rep_t;
        rep_t d = chrono::duration_cast<duration_t>(from).count();
        rep_t sec = d/1000000000;
        rep_t nsec = d%1000000000;
        return  posix_time::seconds(static_cast<long long>(sec))+
            #ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
                posix_time::nanoseconds(nsec);
            #else
                posix_time::microseconds((nsec+500)/1000);
            #endif
      }
    };
    //! @brief @c implicit_converter specialization for conversions from @c boost::posix_time::time_duration to @c boost::chrono::duration<>.
    //!

    template < class Rep, class Period>
    struct implicit_converter_cp<chrono::duration<Rep, Period>, posix_time::time_duration
        > : true_type
    {
      //! @Returns the duration cast from a nanoseconds duration initialized to the total number of nanosecond of the @c from parameter.
      chrono::duration<Rep, Period> operator()(posix_time::time_duration const & from)
      {
        return  chrono::duration_cast<chrono::duration<Rep, Period> >(chrono::nanoseconds(from.total_nanoseconds()));
      }
    };

  }
}

#endif

