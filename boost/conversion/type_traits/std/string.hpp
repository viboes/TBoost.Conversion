//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/type_traits for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief Type traits specializations for <string> types.
 */

#ifndef BOOST_CONVERSION_TT_STD_STRING_HPP
#define BOOST_CONVERSION_TT_STD_STRING_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <string>


namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template<typename CharT, typename Traits, typename Alloc>
  struct is_constructible< std::basic_string<CharT,Traits,Alloc> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template<typename CharT, typename Traits, typename Alloc>
  struct is_constructible< std::basic_string<CharT,Traits,Alloc>, std::basic_string<CharT,Traits,Alloc> const& >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  template<typename CharT, typename Traits, typename Alloc>
  struct is_assignable< std::basic_string<CharT,Traits,Alloc>&, std::basic_string<CharT,Traits,Alloc> const& >  : true_type {};
  template<typename CharT, typename Traits, typename Alloc>
  struct is_assignable< std::basic_string<CharT,Traits,Alloc>, std::basic_string<CharT,Traits,Alloc>  >  : true_type {};
#endif

  template<typename T, typename CharT, typename Traits, typename Alloc>
  struct is_assignable< std::basic_string<CharT,Traits,Alloc>, T >
      : false_type
        {};

}

#endif

