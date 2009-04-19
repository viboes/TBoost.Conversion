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

#include <boost/rational.hpp>
#include <boost/conversion/convert_to.hpp>

namespace boost {

    namespace partial_specialization_workaround {
        template < class T, class U>
        struct convert_to< rational<T>, rational<U> > {
            inline static rational<T> apply(rational<U> const & from)
            {
                return rational<T>(boost::convert_to<T>(from.numerator()), boost::convert_to<T>(from.denominator()));
            }
        };
        template < class T, class U>
        struct assign_to< rational<T>, rational<U> > {
            inline static rational<T>& apply(const rational<U>& from, rational<T>& to)
            {
                to.assign(boost::convert_to<T>(from.numerator()), boost::convert_to<T>(from.denominator()));
                return to;
            }
        };

    }
}

#endif

