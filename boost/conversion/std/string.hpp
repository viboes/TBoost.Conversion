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
 Include this file when using conversions from/to @c std::string.
 */


#ifndef BOOST_CONVERSION_STD_STRING_HPP
#define BOOST_CONVERSION_STD_STRING_HPP

#include <boost/conversion/type_traits/std/string.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#if !defined(BOOST_CONVERSION_USE_CONVERT)
#include <boost/lexical_cast.hpp>
#else
#include <boost/convert/convert.hpp>
#endif


namespace boost {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  //! trick to generate the doc. Don't take care of it
  struct trick_string{};
#endif

  namespace conversion {

    // std namespace can not be overloaded

    /**
     * Partial specialization of @c explicit_converter_cp for convertibles to std::string.
     */
    template<typename T, typename CharT, typename Traits, typename Alloc>
    struct explicit_converter_cp< std::basic_string<CharT,Traits,Alloc>, T
    > : true_type
    {
      std::basic_string<CharT,Traits,Alloc> operator()(T const & from)
      {
#if !defined(BOOST_CONVERSION_USE_CONVERT)
        return lexical_cast<std::basic_string<CharT,Traits,Alloc> >(from);
#else
        return convert<std::basic_string<CharT,Traits,Alloc> >::from(from);
#endif
      }
    };

    /**
     * Partial specialization of @c explicit_converter_cp for convertibles from std::string.
     */
    template<typename T, typename CharT, typename Traits, typename Alloc>
    struct explicit_converter_cp< T, std::basic_string<CharT,Traits,Alloc>
        > : true_type
    {
      T operator()(std::basic_string<CharT,Traits,Alloc> const & from)
      {
#if !defined(BOOST_CONVERSION_USE_CONVERT)
        return lexical_cast<T>(from);
#else
        return convert<T>::from(from);
#endif
      }
    };

  }
}

#endif

