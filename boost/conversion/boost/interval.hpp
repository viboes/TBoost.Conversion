//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO_PAIR__HPP
#define BOOST_CONVERT_TO_PAIR__HPP

#include <boost/numeric/interval.hpp>
#include <boost/conversion/convert_to.hpp>

namespace boost {

    namespace partial_specialization_workaround {
        template < class T, class PT, class U, class PU>
        struct convert_to< numeric::interval<T,PT>, numeric::interval<U,PU> > {
            inline static numeric::interval<T,PT> apply(numeric::interval<U,PU> const & from)
            {
                return numeric::interval<T,PT>(boost::convert_to<T>(from.lower()), boost::convert_to<U>(from.upper()));
            }
        };
        template < class T, class PT, class U, class PU>
        struct assign_to< numeric::interval<T,PT>, numeric::interval<U,PU> > {
            inline static numeric::interval<T,PT>& apply(const numeric::interval<U,PU>& from, numeric::interval<T,PT>& to)
            {
                to.assign(boost::convert_to<T>(from.lower()), boost::convert_to<U>(from.upper()));
                return to;
            }
        };

    }
}

#endif

