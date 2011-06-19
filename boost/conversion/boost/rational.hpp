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
 Include this file when using conversions between @c boost::rational<> of convertible types.
 */


#ifndef BOOST_CONVERSION_PAIR__HPP
#define BOOST_CONVERSION_PAIR__HPP

#include <boost/rational.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
  namespace conversion {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED2)
    /** @brief Added here only to favor generation of specializations with doxygen */
    template < class Target, class Source, class Enable=void>
    struct converter_cp{};
#endif

    //! @brief @c converter specialization for source and target been @c boost::rational.
    //!
    template < class Target, class Source>
    struct converter_cp< rational<Target>, rational<Source>
      BOOST_CONVERSION_REQUIRES((
        is_extrinsic_convertible<Source,Target>::value
      ))
    > : true_type
    {
      //! @Returns the target rational having as numerator and denominator the conversion from the numerator and denominator of the source rational.
      rational<Target> operator()(rational<Source> const & from)
      {
        return rational<Target>(boost::conversion::convert_to<Target>(from.numerator()), boost::conversion::convert_to<Target>(from.denominator()));
      }
    };
    template < class Target, class Source>
    struct assigner_cp< rational<Target>, rational<Source>
      BOOST_CONVERSION_REQUIRES((
        is_extrinsic_convertible<Source,Target>::value
      ))
    > : true_type
    {
      rational<Target>& operator()(rational<Target>& to, const rational<Source>& from)
      {
        to.assign(boost::conversion::convert_to<Target>(from.numerator()), boost::conversion::convert_to<Target>(from.denominator()));
        return to;
      }
    };
  }

#if defined(BOOST_CONVERSION_DOUBLE_CP)
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  template < class Target, class Source>
  inline rational<Target>& assign_to(rational<Target>& to, const rational<Source>& from)
  {
    return conversion::assigner<rational<Target>, rational<Source> >()(to, from);
  }
#endif
#endif

}

#endif

