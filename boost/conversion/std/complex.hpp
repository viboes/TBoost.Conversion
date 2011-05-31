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
 Include this file when using conversions between @c std::complex<> of convertible types.
 */

#ifndef BOOST_CONVERSION_STD_COMPLEX_HPP
#define BOOST_CONVERSION_STD_COMPLEX_HPP

#include <complex>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
  namespace conversion {

    // std namespace can not be overloaded
    namespace overload_workaround {
      /**
       * Partial specialization of @c convert_to for @c std::complex of the same size
       */
      template < class T, class U>
      struct convert_to< std::complex<T>, std::complex<U> > {
        inline static std::complex<T> apply(std::complex<U> const & from)
        {
          return std::complex<T>(
              boost::conversion::convert_to<T>(from.real()),
              boost::conversion::convert_to<T>(from.imag()));
        }
      };
      template < class T, class U>
      struct assign_to< std::complex<T>, std::complex<U> > {
        inline static std::complex<T>& apply(std::complex<T>& to, const std::complex<U>& from)
        {
          to.real() = boost::conversion::convert_to<T>(from.real());
          to.imag() = boost::conversion::convert_to<T>(from.imag());
          return to;
        }
      };

    }
  }
}

#endif

