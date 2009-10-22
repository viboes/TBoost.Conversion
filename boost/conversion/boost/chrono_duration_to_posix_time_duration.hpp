//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO_CHRONO_DURATION_TO_POSIX_TIME_DURATION__HPP
#define BOOST_CONVERT_TO_CHRONO_DURATION_TO_POSIX_TIME_DURATION__HPP

#include <boost/chrono/chrono.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {

    namespace partial_specialization_workaround {
        template < class Rep, class Period>
        struct convert_to<posix_time::time_duration, chrono::duration<Rep, Period> > {
            inline static posix_time::time_duration apply(chrono::duration<Rep, Period> const & from)
            {
                typedef chrono::duration<Rep, Period> src_duration_t;
                typedef chrono::nanoseconds duration_t;
                typedef duration_t::rep rep_t;
                rep_t d = chrono::duration_cast<duration_t>(from).count();
                rep_t sec = d/1000000000;
                rep_t nsec = d%1000000000;
                return  boost::posix_time::seconds(static_cast<long>(sec))+
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
                        boost::posix_time::nanoseconds(nsec);
#else
                        boost::posix_time::microseconds((nsec+500)/1000);
#endif
            }
        };
        template < class Rep, class Period>
        struct assign_to<posix_time::time_duration, chrono::duration<Rep, Period> > {        
            inline static posix_time::time_duration& apply(posix_time::time_duration& to, const chrono::duration<Rep, Period>& from)
            {
                to = boost::convert_to<posix_time::time_duration>(from);
                return to;
            }
        };

        template < class Rep, class Period>
        struct convert_to<chrono::duration<Rep, Period>, posix_time::time_duration> {
            inline static chrono::duration<Rep, Period> apply(posix_time::time_duration const & from)
            {
                return  chrono::duration_cast<chrono::duration<Rep, Period> >(chrono::nanoseconds(from.total_nanoseconds()));
            }
        };
        template < class Rep, class Period>
        struct assign_to<chrono::duration<Rep, Period>, posix_time::time_duration> {
            inline static chrono::duration<Rep, Period> & apply(chrono::duration<Rep, Period> & to, const posix_time::time_duration& from)
            {
                to = boost::convert_to<chrono::duration<Rep, Period> >(from);
                return to;
            }
        };
    }
}

#endif

