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

#include <boost/fusion/tuple.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

//#define BOOST_CONVERSION_NO_FUNCTION_TEMPLATE_ORDERING 1

namespace boost {

    #ifdef BOOST_CONVERSION_NO_FUNCTION_TEMPLATE_ORDERING
    namespace conversion { namespace partial_specialization_workaround {
        template < class T1, class T2, class U1, class U2>
        struct convert_to< boost::fusion::tuple<T1,T2>, boost::fusion::tuple<U1,U2> > {
            inline static boost::fusion::tuple<T1,T2> apply(boost::fusion::tuple<U1,U2> const & from)
            {
                return boost::fusion::tuple<T1,T2>(
                    conversion::convert_to<T1>(boost::fusion::get<0>(from))
                    , conversion::convert_to<T2>(boost::fusion::get<1>(from))
                );
            }
        };
        template < class T1, class T2, class U1, class U2>
        struct assign_to< boost::fusion::tuple<T1,T2>, boost::fusion::tuple<U1,U2> > {
            inline static boost::fusion::tuple<T1,T2>& apply(boost::fusion::tuple<T1,T2>& to, boost::fusion::tuple<U1,U2> const & from)
            {
                to = conversion::convert_to<boost::fusion::tuple<T1,T2> >(from);
                return to;
            }
        };
        template < class T1, class T2, class T3, class U1, class U2, class U3>
        struct convert_to< boost::fusion::tuple<T1,T2,T3>, boost::fusion::tuple<U1,U2,U3> > {
            inline static boost::fusion::tuple<T1,T2,T3> apply(boost::fusion::tuple<U1,U2,U3> const & from)
            {
                return boost::fusion::tuple<T1,T2, T3>(
                      conversion::convert_to<T1>(boost::fusion::get<0>(from))
                    , conversion::convert_to<T2>(boost::fusion::get<1>(from))
                    , conversion::convert_to<T3>(boost::fusion::get<2>(from))
                );
            }
        };
        template < class T1, class T2, class T3, class U1, class U2, class U3>
        struct assign_to< boost::fusion::tuple<T1,T2,T3>, boost::fusion::tuple<U1,U2,U3> > {
            inline static boost::fusion::tuple<T1,T2,T3> apply(boost::fusion::tuple<T1,T2,T3>& to, boost::fusion::tuple<U1,U2,U3> const & from)
            {
                to = conversion::convert_to<boost::fusion::tuple<T1,T2> >(from);
                return to;
            }
        };

    }}
    #else
    namespace fusion {
    template < class T1, class T2, class U1, class U2>
    inline static tuple<T1,T2> convert_to(tuple<U1,U2> const & from
                    , boost::dummy::type_tag<tuple<T1,T2> >)
    {
        return tuple<T1,T2>(
            conversion::convert_to<T1>(boost::fusion::get<0>(from))
            , conversion::convert_to<T2>(boost::fusion::get<1>(from))
        );
    }

    template < class T1, class T2, class U1, class U2>
    inline static tuple<T1,T2>& assign_to(tuple<T1,T2>& to, tuple<U1,U2> const & from)
    {
        to = conversion::convert_to<boost::fusion::tuple<T1,T2> >(from);
        return to;
    }

    template < class T1, class T2, class T3, class U1, class U2, class U3>
    inline static tuple<T1,T2,T3> convert_to(tuple<U1,U2,U3> const & from
                    , boost::dummy::type_tag<tuple<T1,T2,T3> >)
    {
        return boost::fusion::tuple<T1,T2, T3>(
                conversion::convert_to<T1>(boost::fusion::get<0>(from))
            , conversion::convert_to<T2>(boost::fusion::get<1>(from))
            , conversion::convert_to<T3>(boost::fusion::get<2>(from))
        );
    }

    template < class T1, class T2, class T3, class U1, class U2, class U3>
    inline static tuple<T1,T2,T3> assign_to(tuple<T1,T2,T3>& to, boost::fusion::tuple<U1,U2,U3> const & from)
    {
        to = conversion::convert_to<boost::fusion::tuple<T1,T2> >(from);
        return to;
    }
    }
    #endif
}

#endif

