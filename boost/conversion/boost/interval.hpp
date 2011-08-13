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
 Include this file when using conversions between @c boost::numeric::interval<> of convertible types.
 */

#ifndef BOOST_CONVERSION_INTERVAL_HPP
#define BOOST_CONVERSION_INTERVAL_HPP

#include <boost/conversion/type_traits/boost/numeric/interval.hpp>
#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
  #if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    //! trick to generate the doc. Don't take care of it
    struct trick_numeric_interval{};
  #endif
  
  namespace conversion {

    //! @brief @c implicit_converter specialization for source and target been @c boost::numeric::interval.
    //!
    template < typename Target, typename PTarget, typename Source, typename PSource>
    struct implicit_converter_cp< numeric::interval<Target,PTarget>, numeric::interval<Source,PSource>
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(
        ExtrinsicallyConvertible<Source,Target>
        )
#else
        , typename enable_if_c<
        is_extrinsically_convertible<Source,Target>::value
        >::type
#endif
    > : true_type
    {
      //! @Returns the target interval having as extremes the conversion from the source interval extremes.
      numeric::interval<Target,PTarget> operator()(numeric::interval<Source,PSource> const & from)
      {
        return numeric::interval<Target,PTarget>(boost::conversion::implicit_convert_to<Target>(from.lower()), boost::conversion::implicit_convert_to<Source>(from.upper()));
      }
    };
    template < typename Target, typename PTarget, typename Source, typename PSource>
    struct assigner_cp< numeric::interval<Target,PTarget>, numeric::interval<Source,PSource>
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(
        ExtrinsicallyConvertible<Source,Target>
        )
#else
        , typename enable_if_c<
        is_extrinsically_convertible<Source,Target>::value
        >::type
#endif
    > : true_type
    {
      numeric::interval<Target,PTarget>& operator()(numeric::interval<Target,PTarget>& to, const numeric::interval<Source,PSource>& from)
      {
        to.assign(boost::conversion::implicit_convert_to<Target>(from.lower()), boost::conversion::implicit_convert_to<Source>(from.upper()));
        return to;
      }
    };
  }
}

#endif

