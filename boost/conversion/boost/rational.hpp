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
 Include this file when using conversions between @c boost::rational<> of convertible types.
 */

#ifndef BOOST_CONVERSION_PAIR__HPP
#define BOOST_CONVERSION_PAIR__HPP

#include <boost/rational.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>

namespace boost {

    #ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING && ! defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace conversion { namespace overload_workaround {
        template < class T, class U>
        struct convert_to< rational<T>, rational<U> > {
            inline static rational<T> apply(rational<U> const & from)
            {
                return rational<T>(boost::conversion::convert_to<T>(from.numerator()), boost::conversion::convert_to<T>(from.denominator()));
            }
        };
        template < class T, class U>
        struct assign_to< rational<T>, rational<U> > {
            inline static rational<T>& apply(rational<T>& to, const rational<U>& from)
            {
                to.assign(boost::conversion::convert_to<T>(from.numerator()), boost::conversion::convert_to<T>(from.denominator()));
                return to;
            }
        };

    }}
    #else
    //! @brief @c convert_to overloading for source and target been @c boost::rational.
    //!
    //! @Returns the target rational having as numerator and denominator the conversion from the numerator and denominator of the source rational.
    template < class T, class U>
    inline rational<T> convert_to(rational<U> const & from
                        , boost::dummy::type_tag<rational<T> > const&)
    {
        return rational<T>(boost::conversion::convert_to<T>(from.numerator()), boost::conversion::convert_to<T>(from.denominator()));
    }

    template < class T, class U>
    inline rational<T>& assign_to(rational<T>& to, const rational<U>& from
                        , boost::dummy::type_tag<rational<T> > const&
    )
    {
        to.assign(boost::conversion::convert_to<T>(from.numerator()), boost::conversion::convert_to<T>(from.denominator()));
        return to;
    }
    #endif


}

#endif

