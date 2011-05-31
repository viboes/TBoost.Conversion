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
 \file
 \brief
 Include this file when using conversions between @c boost::ptime and @c boost::chrono::time_point<>.
 */

//[CHRONO_TIME_POINT_TO_POSIX_TIME_PTIME_HPP
#ifndef BOOST_CONVERSION_CHRONO_TIME_POINT_TO_POSIX_TIME_PTIME_HPP
#define BOOST_CONVERSION_CHRONO_TIME_POINT_TO_POSIX_TIME_PTIME_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/conversion.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>

namespace boost {
    #ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING && ! defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace conversion { namespace overload_workaround {
        template < class Clock, class Duration>
        struct convert_to<posix_time::ptime, chrono::time_point<Clock, Duration> > {
            inline static posix_time::ptime apply(const chrono::time_point<Clock, Duration>& from)
            {
                typedef chrono::time_point<Clock, Duration> time_point_t;
                typedef chrono::nanoseconds duration_t;
                typedef duration_t::rep rep_t;
                rep_t d = chrono::duration_cast<duration_t>(from.time_since_epoch()).count();
                rep_t sec = d/1000000000;
                rep_t nsec = d%1000000000;
                return  posix_time::from_time_t(0)+
                        posix_time::seconds(static_cast<long>(sec))+
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
                        posix_time::nanoseconds(nsec);
#else
                        posix_time::microseconds((nsec+500)/1000);
#endif
            }
        };
        template < class Clock, class Duration>
        struct assign_to<posix_time::ptime, chrono::time_point<Clock, Duration> > {
            inline static posix_time::ptime& apply(posix_time::ptime& to, const chrono::time_point<Clock, Duration>& from)
            {
                to = boost::conversion::convert_to<posix_time::ptime>(from);
                return to;
            }
        };

        template < class Clock, class Duration>
        struct convert_to<chrono::time_point<Clock, Duration>, posix_time::ptime> {
            inline static chrono::time_point<Clock, Duration> apply(const posix_time::ptime& from)
            {
                posix_time::time_duration const time_since_epoch=from-posix_time::from_time_t(0);
                chrono::time_point<Clock, Duration> t=chrono::system_clock::from_time_t(time_since_epoch.total_seconds());
                long long nsec=time_since_epoch.fractional_seconds()*(1000000000/time_since_epoch.ticks_per_second());
                return  t+chrono::duration_cast<Duration>(chrono::nanoseconds(nsec));
            }
        };
        template < class Clock, class Duration>
        struct assign_to<chrono::time_point<Clock, Duration>, posix_time::ptime> {
            inline static chrono::time_point<Clock, Duration>& apply(chrono::time_point<Clock, Duration>& to, const posix_time::ptime& from)
            {
                to = boost::conversion::convert_to<chrono::time_point<Clock, Duration> >(from);
                return to;
            }
        };
    }}
    #else
    namespace chrono {
        template < class Clock, class Duration>
        inline posix_time::ptime convert_to(const chrono::time_point<Clock, Duration>& from
                    , conversion::dummy::type_tag<posix_time::ptime> const&)
        {
                typedef chrono::time_point<Clock, Duration> time_point_t;
                typedef chrono::nanoseconds duration_t;
                typedef duration_t::rep rep_t;
                rep_t d = chrono::duration_cast<duration_t>(from.time_since_epoch()).count();
                rep_t sec = d/1000000000;
                rep_t nsec = d%1000000000;
                return  posix_time::from_time_t(0)+
                        posix_time::seconds(static_cast<long>(sec))+
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
                        posix_time::nanoseconds(nsec);
#else
                        posix_time::microseconds((nsec+500)/1000);
#endif
        }


        template < class Clock, class Duration>
        inline chrono::time_point<Clock, Duration>& assign_to(chrono::time_point<Clock, Duration>& to, const posix_time::ptime& from
        )
        {
            to = boost::conversion::convert_to<chrono::time_point<Clock, Duration> >(from);
            return to;
        }

    }

    namespace posix_time {
        template < class TP>
        inline TP convert_to(const ptime& from
                , conversion::dummy::type_tag<TP > const&)
        {
            time_duration const time_since_epoch=from-from_time_t(0);
            TP t=chrono::system_clock::from_time_t(time_since_epoch.total_seconds());
            long long nsec=time_since_epoch.fractional_seconds()*(1000000000/time_since_epoch.ticks_per_second());
            return  t+chrono::duration_cast<typename TP::duration>(chrono::nanoseconds(nsec));
        }


        template < class Clock, class Duration>
        inline ptime& assign_to(ptime& to, const chrono::time_point<Clock, Duration>& from
        )
        {
            to = boost::conversion::convert_to<ptime>(from);
            return to;
        }

    }
    #endif
}

#endif
//]
