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

#include <boost/tr1/tuple>
#include <boost/conversion/convert_to.hpp>

namespace boost {

    namespace partial_specialization_workaround {
        template < class T1, class T2, class U1, class U2>
        struct convert_to< std::tr1::tuple<T1,T2>, std::tr1::tuple<U1,U2> > {
            inline static std::tr1::tuple<T1,T2> apply(std::tr1::tuple<U1,U2> const & from)
            {
                return std::tr1::tuple<T1,T2>(
                    convert_to<T1>(std::tr1::get<0>(from)) 
                    , convert_to<T2>(std::tr1::get<1>(from))
                );
            }
            inline static std::tr1::tuple<T1,T2>& apply(std::tr1::tuple<U1,U2> const & from, std::tr1::tuple<T1,T2>& to)
            {
                to = boost::convert(from);
                return to;
            }
        };
        template < class T1, class T2, class T3, class U1, class U2, class U3>
        struct convert_to< std::tr1::tuple<T1,T2,T3>, std::tr1::tuple<U1,U2,U3> > {
            inline static std::tr1::tuple<T1,T2,T3> apply(std::tr1::tuple<U1,U2,U3> const & from)
            {
                return std::tr1::tuple<T1,T2, T3>(
                      convert_to<T1>(std::tr1::get<0>(from)) 
                    , convert_to<T2>(std::tr1::get<1>(from))
                    , convert_to<T3>(std::tr1::get<2>(from))
                );
            }
            inline static std::tr1::tuple<T1,T2,T3> apply(std::tr1::tuple<U1,U2,U3> const & from, std::tr1::tuple<T1,T2,T3>& to)
            {
                to = boost::convert(from);
                return to;
            }
        };

    }
}

#endif

