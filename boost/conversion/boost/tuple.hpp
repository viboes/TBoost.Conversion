//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/*!
 \file
 \brief
 Include this file when using conversions between @c boost::fusion::tuple<> of convertible types.
 */
#ifndef BOOST_CONVERSION_TUPLE_HPP
#define BOOST_CONVERSION_TUPLE_HPP

#include <boost/fusion/tuple.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>

namespace boost {

  namespace conversion {
    namespace overload_workaround {
        template < class T1, class T2, class U1, class U2>
        struct convert_to< fusion::tuple<T1,T2>, fusion::tuple<U1,U2> > {
            inline static fusion::tuple<T1,T2> apply(fusion::tuple<U1,U2> const & from)
            {
                return fusion::tuple<T1,T2>(
                    boost::conversion::convert_to<T1>(fusion::get<0>(from))
                    , boost::conversion::convert_to<T2>(fusion::get<1>(from))
                );
            }
        };
        template < class T1, class T2, class T3, class U1, class U2, class U3>
        struct convert_to< fusion::tuple<T1,T2,T3>, fusion::tuple<U1,U2,U3> > {
            inline static fusion::tuple<T1,T2,T3> apply(fusion::tuple<U1,U2,U3> const & from)
            {
                return fusion::tuple<T1,T2, T3>(
                      boost::conversion::convert_to<T1>(fusion::get<0>(from))
                    , boost::conversion::convert_to<T2>(fusion::get<1>(from))
                    , boost::conversion::convert_to<T3>(fusion::get<2>(from))
                );
            }
        };

    }
  }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    namespace fusion {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
      template < class... Target, class... Source>
      inline tuple<Target...>& assign_to(tuple<Target...>& to, tuple<Source...> const & from
      )
#else

    template < class T1, class T2, class U1, class U2>
    inline tuple<T1,T2>& assign_to(tuple<T1,T2>& to, tuple<U1,U2> const & from
    )
    {
        to = boost::conversion::convert_to<boost::fusion::tuple<T1,T2> >(from);
        return to;
    }

    template < class T1, class T2, class T3, class U1, class U2, class U3>
    inline tuple<T1,T2,T3> assign_to(tuple<T1,T2,T3>& to, boost::fusion::tuple<U1,U2,U3> const & from
    )
    {
        to = boost::conversion::convert_to<boost::fusion::tuple<T1,T2> >(from);
        return to;
    }
    }
#endif
#endif
}

#endif

