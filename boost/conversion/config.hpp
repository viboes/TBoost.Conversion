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

//#define BOOST_CONVERSION_USES_SFINAE

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
  #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
  #else
    #define BOOST_CONVERSION_IMPLICITLY_ENABLED
  #endif
#endif

#endif

