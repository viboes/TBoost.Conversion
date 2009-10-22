//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[CHRONO_TIME_POINT_TO_POSIX_TIME_PTIME__HPP
#ifndef BOOST_CONVERT_TO_CHRONO_TIME_POINT_TO_POSIX_TIME_PTIME__HPP
#define BOOST_CONVERT_TO_CHRONO_TIME_POINT_TO_POSIX_TIME_PTIME__HPP

#include <boost/chrono/chrono.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/conversion.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {

    namespace partial_specialization_workaround {
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
                return  boost::posix_time::from_time_t(0)+
                        boost::posix_time::seconds(static_cast<long>(sec))+
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
                        boost::posix_time::nanoseconds(nsec);
#else
                        boost::posix_time::microseconds((nsec+500)/1000);
#endif
            }
        };
        template < class Clock, class Duration>
        struct assign_to<posix_time::ptime, chrono::time_point<Clock, Duration> > {
            inline static posix_time::ptime& apply(posix_time::ptime& to, const chrono::time_point<Clock, Duration>& from)
            {
                to = boost::convert_to<posix_time::ptime>(from);
                return to;
            }
        };
        
        template < class Clock, class Duration>
        struct convert_to<chrono::time_point<Clock, Duration>, posix_time::ptime> {
            inline static chrono::time_point<Clock, Duration> apply(const posix_time::ptime& from)
            {
                boost::posix_time::time_duration const time_since_epoch=from-boost::posix_time::from_time_t(0);
                chrono::time_point<Clock, Duration> t=chrono::system_clock::from_time_t(time_since_epoch.total_seconds());
                long nsec=time_since_epoch.fractional_seconds()*(1000000000/time_since_epoch.ticks_per_second());
                return  t+chrono::nanoseconds(nsec);
                
            }
        };
        template < class Clock, class Duration>
        struct assign_to<chrono::time_point<Clock, Duration>, posix_time::ptime> {
            inline static chrono::time_point<Clock, Duration>& apply(chrono::time_point<Clock, Duration>& to, const posix_time::ptime& from)
            {
                to = boost::convert_to<chrono::time_point<Clock, Duration> >(from);
                return to;
            }
        };
    }
}

#endif
//]
