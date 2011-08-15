//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @file
 * @brief Defines the free function @c convert_to.
 *
 *  The @c convert_to function converts the @c from parameter to a @c Target type.
 *
 */
#ifndef BOOST_CONVERSION_CONVERT_TO_HPP
#define BOOST_CONVERSION_CONVERT_TO_HPP


#include <boost/conversion/explicit_convert_to.hpp>
#include <boost/conversion/is_extrinsically_explicit_convertible.hpp>

namespace boost {

  namespace conversion {



    //! @brief Extrinsic conversion function.
    //! Converts the @c from parameter to an instance of the @c Target type.
    //! This function can be seen as an emulation of free function overload of the explicit conversion operator.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Params
    //! @Param{source,source of the conversion}
    //!
    //! @Returns The result of @c explicit_convert_to<Target>(from).
    //! @Throws  Whatever the @c explicit_convert_to<Target>(from) throws.
    //!
    //! This function doesn't participate on overload resolution when @c conversion::enable_functor<Source>::type is mpl::true_.
    template <typename Target, typename Source>
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    //typename disable_if<typename conversion::enable_functor<Source>::type, Target>::type
    typename enable_if_c<
      conversion::is_extrinsically_explicit_convertible<Source,Target>::value,
      Target
    >::type
#else
    Target
#endif
    convert_to(Source const& from)
    {
      return boost::conversion::explicit_convert_to<Target>(from);
    }
  }
}

#endif

