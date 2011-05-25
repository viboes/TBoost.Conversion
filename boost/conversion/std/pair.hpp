//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/*!
 \file
 \brief
 Include this file when using conversions between @c std::pair<> of convertible types.
 */

//[PAIR_HPP
#ifndef BOOST_CONVERSION_STD_PAIR_HPP
#define BOOST_CONVERSION_STD_PAIR_HPP

#include <utility>
//#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost { namespace conversion {

    // std namespace can not be overloaded
    namespace overload_workaround {
        template < class T1, class T2, class U1, class U2>
        struct convert_to< std::pair<T1,T2>, std::pair<U1,U2> > {
            inline static std::pair<T1,T2> apply(std::pair<U1,U2> const & from)
            {
                return std::pair<T1,T2>(boost::conversion::convert_to<T1>(from.first), boost::conversion::convert_to<T2>(from.second));
            }
        };
        template < class T1, class T2, class U1, class U2>
        struct assign_to< std::pair<T1,T2>, std::pair<U1,U2> > {
            inline static std::pair<T1,T2>& apply(std::pair<T1,T2>& to, const std::pair<U1,U2>& from)
            {
                to.first = boost::conversion::convert_to<T1>(from.first);
                to.second = boost::conversion::convert_to<T2>(from.second);
                return to;
            }
        };
    }
}}

#endif

//]
