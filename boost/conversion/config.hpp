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
    #if defined _MSC_VER
       #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
    #elif defined __clang__
         #define BOOST_CONVERSION_ENABLE_CND
    #elif defined __GNUC__
       #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
         #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
       #endif
       #define BOOST_CONVERSION_ENABLE_CND
    #else
      #define BOOST_CONVERSION_ENABLE_CND
    #endif
  #else
    #if defined _MSC_VER
       #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
    #elif defined __clang__
         #define BOOST_CONVERSION_ENABLE_CND
         //#define BOOST_CONVERSION_NO_IS_ASSIGNABLE
    #elif defined __GNUC__
       #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
         #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
       #endif
       #define BOOST_CONVERSION_ENABLE_CND
    #else
       #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
    #endif
  #endif
#endif

#if !defined BOOST_CONVERSION_ENABLE_CND
#define BOOST_CONVERSION_ENABLE_CND
#endif

#if defined(BOOST_CONVERSION_ENABLE_CND) && !defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
  #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
  #else
    #define BOOST_CONVERSION_MCF_ENABLED
  #endif
#endif

#endif

