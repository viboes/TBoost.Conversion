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
 @ile
 @brief
 Include this file when using conversions between @c boost::numeric::interval<> of convertible types.
 */

#ifndef BOOST_CONVERSION_INTERVAL_HPP
#define BOOST_CONVERSION_INTERVAL_HPP

#include <boost/numeric/interval.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {

    namespace conversion {
      namespace overload_workaround {
        //! @brief @c convert_to specialization for source and target been @c boost::numeric::interval.
        //!
        template < class T, class PT, class U, class PU>
        struct convert_to< numeric::interval<T,PT>, numeric::interval<U,PU> > {
          //! @Returns the target interval having as extremes the conversion from the source interval extremes.
            inline static numeric::interval<T,PT> apply(numeric::interval<U,PU> const & from)
            {
                return numeric::interval<T,PT>(boost::conversion::convert_to<T>(from.lower()), boost::conversion::convert_to<U>(from.upper()));
            }
        };
        template < class T, class PT, class U, class PU>
        struct assign_to< numeric::interval<T,PT>, numeric::interval<U,PU> > {
            inline static numeric::interval<T,PT>& apply(numeric::interval<T,PT>& to, const numeric::interval<U,PU>& from)
            {
                to.assign(boost::conversion::convert_to<T>(from.lower()), boost::conversion::convert_to<U>(from.upper()));
                return to;
            }
        };
      }
    }
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    namespace numeric {
        template < class T, class PT, class U, class PU>
        inline interval<T,PT>& assign_to(interval<T,PT>& to, const interval<U,PU>& from
        )
        {
          return conversion::overload_workaround::assign_to<interval<T,PT>, interval<U,PU> >::apply(to, from);
        }
    }
#endif
}

#endif

