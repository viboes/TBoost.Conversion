//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO_TUPLE_HPP
#define BOOST_CONVERT_TO_TUPLE_HPP

#include <boost/fusion/tuple.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>

namespace boost {

    #ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    namespace conversion { namespace partial_specialization_workaround {
        template < class T1, class T2, class U1, class U2>
        struct convert_to< fusion::tuple<T1,T2>, fusion::tuple<U1,U2> > {
            inline static fusion::tuple<T1,T2> apply(fusion::tuple<U1,U2> const & from)
            {
                return fusion::tuple<T1,T2>(
                    boost::convert_to<T1>(fusion::get<0>(from))
                    , boost::convert_to<T2>(fusion::get<1>(from))
                );
            }
        };
        template < class T1, class T2, class U1, class U2>
        struct assign_to< fusion::tuple<T1,T2>, fusion::tuple<U1,U2> > {
            inline static fusion::tuple<T1,T2>& apply(fusion::tuple<T1,T2>& to, fusion::tuple<U1,U2> const & from)
            {
                to = boost::convert_to<fusion::tuple<T1,T2> >(from);
                return to;
            }
        };
        template < class T1, class T2, class T3, class U1, class U2, class U3>
        struct convert_to< fusion::tuple<T1,T2,T3>, fusion::tuple<U1,U2,U3> > {
            inline static fusion::tuple<T1,T2,T3> apply(fusion::tuple<U1,U2,U3> const & from)
            {
                return fusion::tuple<T1,T2, T3>(
                      boost::convert_to<T1>(fusion::get<0>(from))
                    , boost::convert_to<T2>(fusion::get<1>(from))
                    , boost::convert_to<T3>(fusion::get<2>(from))
                );
            }
        };
        template < class T1, class T2, class T3, class U1, class U2, class U3>
        struct assign_to< fusion::tuple<T1,T2,T3>, fusion::tuple<U1,U2,U3> > {
            inline static fusion::tuple<T1,T2,T3> apply(fusion::tuple<T1,T2,T3>& to, fusion::tuple<U1,U2,U3> const & from)
            {
                to = boost::convert_to<fusion::tuple<T1,T2> >(from);
                return to;
            }
        };

    }}
    #else
    namespace fusion {
    template < class T1, class T2, class U1, class U2>
    inline tuple<T1,T2> convert_to(tuple<U1,U2> const & from
                    , boost::dummy::type_tag<tuple<T1,T2> > const&)
    {
        return tuple<T1,T2>(
            boost::convert_to<T1>(boost::fusion::get<0>(from))
            , boost::convert_to<T2>(boost::fusion::get<1>(from))
        );
    }

    template < class T1, class T2, class U1, class U2>
    inline tuple<T1,T2>& assign_to(tuple<T1,T2>& to, tuple<U1,U2> const & from
                    , boost::dummy::type_tag<tuple<T1,T2> > const&
    )
    {
        to = boost::convert_to<boost::fusion::tuple<T1,T2> >(from);
        return to;
    }

    template < class T1, class T2, class T3, class U1, class U2, class U3>
    inline tuple<T1,T2,T3> convert_to(tuple<U1,U2,U3> const & from
                    , boost::dummy::type_tag<tuple<T1,T2,T3> > const&
    )
    {
        return boost::fusion::tuple<T1,T2, T3>(
                boost::convert_to<T1>(boost::fusion::get<0>(from))
            , boost::convert_to<T2>(boost::fusion::get<1>(from))
            , boost::convert_to<T3>(boost::fusion::get<2>(from))
        );
    }

    template < class T1, class T2, class T3, class U1, class U2, class U3>
    inline tuple<T1,T2,T3> assign_to(tuple<T1,T2,T3>& to, boost::fusion::tuple<U1,U2,U3> const & from
                    , boost::dummy::type_tag<tuple<T1,T2,T3> > const&
    )
    {
        to = boost::convert_to<boost::fusion::tuple<T1,T2> >(from);
        return to;
    }
    }
    #endif
}

#endif

