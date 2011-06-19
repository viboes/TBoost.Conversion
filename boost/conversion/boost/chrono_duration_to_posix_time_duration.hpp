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

#include <boost/chrono/chrono.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>

namespace boost {
  namespace conversion {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED2)
    /** @brief Added here only to favor generation of specializations with doxygen */
    template < class Target, class Source, class Enable=void>
    struct converter_cp{};
#endif

    //! @brief @c converter specialization for conversions from @c boost::chrono::duration<> to @c boost::posix_time::time_duration.
    //!
    template < class Rep, class Period>
    struct converter_cp<posix_time::time_duration, chrono::duration<Rep, Period>
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
    //! @brief @c converter specialization for conversions from @c boost::posix_time::time_duration to @c boost::chrono::duration<>.
    //!

    template < class Rep, class Period>
    struct converter_cp<chrono::duration<Rep, Period>, posix_time::time_duration
        > : true_type
    {
      //! @Returns the duration cast from a nanoseconds duration initialized to the total number of nanosecond of the @c from parameter.
      chrono::duration<Rep, Period> operator()(posix_time::time_duration const & from)
      {
        return  chrono::duration_cast<chrono::duration<Rep, Period> >(chrono::nanoseconds(from.total_nanoseconds()));
      }
    };

  }

#if defined(BOOST_CONVERSION_DOUBLE_CP)
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  namespace chrono {

    //! @brief @c assign_to overloading for conversions from @c boost::chrono::duration<> to @c boost::posix_time::time_duration.
    //!
    //! @Effects As if <c>to = boost::conversion::convert_to<duration<Rep, Period>>(from)</c>.
    //! @Returns The @c to parameter reference.

    template < class Rep, class Period>
    inline chrono::duration<Rep, Period> & assign_to(chrono::duration<Rep, Period> & to, const posix_time::time_duration& from)
    {
        to = boost::conversion::convert_to<duration<Rep, Period> >(from);
        return to;
    }
  }

  namespace posix_time {

    //! @brief @c assign_to overloading for conversions from @c boost::posix_time::time_duration to @c boost::chrono::duration<>.
    //!
    //! @Effects As if <c>to = boost::conversion::convert_to<time_duration>(from)</c>.
    //! @Returns The @c to parameter reference.
    template < class Rep, class Period>
    inline time_duration& assign_to(time_duration& to, const chrono::duration<Rep, Period>& from)
    {
        to = boost::conversion::convert_to<time_duration>(from);
        return to;
    }
  }

#endif
#endif
}

#endif

