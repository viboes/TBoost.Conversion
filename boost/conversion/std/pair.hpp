//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[PAIR__HPP
#ifndef BOOST_CONVERT_TO_PAIR__HPP
#define BOOST_CONVERT_TO_PAIR__HPP

#include <utility>
//#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost { namespace conversion {

    namespace partial_specialization_workaround {
        template < class T1, class T2, class U1, class U2>
        struct convert_to< std::pair<T1,T2>, std::pair<U1,U2> > {
            inline static std::pair<T1,T2> apply(std::pair<U1,U2> const & from)
            {
                return std::pair<T1,T2>(boost::convert_to<T1>(from.first), boost::convert_to<T2>(from.second));
            }
        };
        template < class T1, class T2, class U1, class U2>
        struct assign_to< std::pair<T1,T2>, std::pair<U1,U2> > {
            inline static std::pair<T1,T2>& apply(std::pair<T1,T2>& to, const std::pair<U1,U2>& from)
            {
                to.first = boost::convert_to<T1>(from.first);
                to.second = boost::convert_to<T2>(from.second);
                return to;
            }
        };
    }
}}

#endif

//]
