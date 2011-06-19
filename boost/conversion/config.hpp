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
 *
 */
#ifndef BOOST_CONVERSION_CONFIG_HPP
#define BOOST_CONVERSION_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp>

#define BOOST_CONVERSION_REQUIRES(CND) \
                , typename enable_if_c< CND >::type

#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
#define BOOST_CONVERSION_ENABLE_CND
#else
  #if ! defined(BOOST_NO_DECLTYPE)
    #if ! defined _MSC_VER
      #define BOOST_CONVERSION_ENABLE_CND
    #endif
  #endif
#endif


#endif

