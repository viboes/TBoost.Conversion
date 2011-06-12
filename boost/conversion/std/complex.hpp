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
 @file
 @brief
 Include this file when using conversions between @c std::complex<> of convertible types.
 */

#ifndef BOOST_CONVERSION_STD_COMPLEX_HPP
#define BOOST_CONVERSION_STD_COMPLEX_HPP

#include <complex>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
  namespace conversion {

    /**
     * Partial specialization of @c convert_to for @c std::complex of the same size
     */
    template < class Target, class Source>
    struct converter_cp< std::complex<Target>, std::complex<Source>
#if defined(BOOST_CONVERSION_ENABLE_CND)
    , typename enable_if_c<
            is_extrinsic_convertible<Source,Target>::value
            //&& ! default_converter_condition< std::complex<Target>, std::complex<Source> >::value
        >::type
#endif
    > : true_type
    {
      std::complex<Target> operator()(std::complex<Source> const & from)
      {
        return std::complex<Target>(
            boost::conversion::convert_to<Target>(from.real()),
            boost::conversion::convert_to<Target>(from.imag()));
      }
    };
    template < class Target, class Source>
    struct assigner_cp< std::complex<Target>, std::complex<Source>
#if defined(BOOST_CONVERSION_ENABLE_CND)
    , typename enable_if_c<
            is_extrinsic_convertible<Source,Target>::value
            //&& ! default_assigner_condition< std::complex<Target>, std::complex<Source> >::value
        >::type
#endif
    > : true_type
    {
      std::complex<Target>& operator()(std::complex<Target>& to, const std::complex<Source>& from)
      {
        to.real() = boost::conversion::convert_to<Target>(from.real());
        to.imag() = boost::conversion::convert_to<Target>(from.imag());
        return to;
      }
    };

  }
}

#endif

