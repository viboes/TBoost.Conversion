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

#include <boost/numeric/interval.hpp>
#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
  namespace conversion {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED2)
    /** @brief Added here only to favor generation of specializations with doxygen */
    template < class Target, class Source, class Enable=void>
    struct implicit_converter_cp{};
#endif


    //! @brief @c converter specialization for source and target been @c boost::numeric::interval.
    //!
    template < class Target, class PTarget, class Source, class PSource>
    struct converter_cp< numeric::interval<Target,PTarget>, numeric::interval<Source,PSource>
      BOOST_CONVERSION_REQUIRES((
          is_extrinsic_convertible<Source,Target>::value
      ))
    > : true_type
    {
      //! @Returns the target interval having as extremes the conversion from the source interval extremes.
      numeric::interval<Target,PTarget> operator()(numeric::interval<Source,PSource> const & from)
      {
        return numeric::interval<Target,PTarget>(boost::conversion::implicit_convert_to<Target>(from.lower()), boost::conversion::implicit_convert_to<Source>(from.upper()));
      }
    };
    template < class Target, class PTarget, class Source, class PSource>
    struct assigner_cp< numeric::interval<Target,PTarget>, numeric::interval<Source,PSource>
      BOOST_CONVERSION_REQUIRES((
        is_extrinsic_convertible<Source,Target>::value
      ))
    > : true_type
    {
      numeric::interval<Target,PTarget>& operator()(numeric::interval<Target,PTarget>& to, const numeric::interval<Source,PSource>& from)
      {
        to.assign(boost::conversion::implicit_convert_to<Target>(from.lower()), boost::conversion::implicit_convert_to<Source>(from.upper()));
        return to;
      }
    };
  }

#if defined(BOOST_CONVERSION_DOUBLE_CP)
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  namespace numeric {
    template < class Target, class PTarget, class Source, class PSource>
    inline interval<Target,PTarget>& assign_to(interval<Target,PTarget>& to, const interval<Source,PSource>& from)
    {
      return conversion::assigner<interval<Target,PTarget>, interval<Source,PSource> >()(to, from);
    }
  }
#endif
#endif
}

#endif

