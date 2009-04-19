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

#include <complex>
#include <boost/conversion/convert_to.hpp>

namespace boost {

    namespace partial_specialization_workaround {
        template < class T, class U>
        struct convert_to< std::complex<T>, std::complex<U> > {
            inline static std::complex<T> apply(std::complex<U> const & from)
            {
                return std::complex<T>(boost::convert_to<T>(from.real()), boost::convert_to<T>(from.imag()));
            }
        };
        template < class T, class U>
        struct assign_to< std::complex<T>, std::complex<U> > {
            inline static std::complex<T>& apply(const std::complex<U>& from, std::complex<T>& to)
            {
                to.real() = boost::convert_to<T>(from.real());
                to.imag() = boost::convert_to<T>(from.imag());
                return to;
            }
        };

    }
}

#endif

