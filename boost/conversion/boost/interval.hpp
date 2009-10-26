//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO_INTERVAL__HPP
#define BOOST_CONVERT_TO_INTERVAL__HPP

#include <boost/numeric/interval.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {

    #if 0
    namespace conversion { namespace partial_specialization_workaround {
        template < class T, class PT, class U, class PU>
        struct convert_to< numeric::interval<T,PT>, numeric::interval<U,PU> > {
            inline static numeric::interval<T,PT> apply(numeric::interval<U,PU> const & from)
            {
                return numeric::interval<T,PT>(boost::convert_to<T>(from.lower()), boost::convert_to<U>(from.upper()));
            }
        };
        template < class T, class PT, class U, class PU>
        struct assign_to< numeric::interval<T,PT>, numeric::interval<U,PU> > {
            inline static numeric::interval<T,PT>& apply(numeric::interval<T,PT>& to, const numeric::interval<U,PU>& from)
            {
                to.assign(boost::convert_to<T>(from.lower()), boost::convert_to<U>(from.upper()));
                return to;
            }
        };

    }}
    #else
    namespace numeric {
        template < class T, class PT, class U, class PU>
        inline static interval<T,PT> convert_to(interval<U,PU> const & from, type_tag<interval<T,PT> >)
        {
            return interval<T,PT>(boost::convert_to<T>(from.lower()), boost::convert_to<U>(from.upper()));
        }
        template < class T, class PT, class U, class PU>
        inline static interval<T,PT>& assign_to(interval<T,PT>& to, const interval<U,PU>& from)
        {
            to.assign(boost::convert_to<T>(from.lower()), boost::convert_to<U>(from.upper()));
            return to;
        }
    }
    #endif
}

#endif

