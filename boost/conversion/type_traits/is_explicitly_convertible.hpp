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
 * @brief
 */


#ifndef BOOST_CONVERSION_TT_IS_EXPLICITLY_CONVERTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_EXPLICITLY_CONVERTIBLE_HPP

#include <boost/conversion/type_traits/is_constructible.hpp>

namespace boost {

  template <class Source, class Target>
  struct is_explicitly_convertible : is_constructible<Target, Source> {};

  template <class Source, class Target>
  struct is_explicitly_convertible2 : true_type {};

}


#endif

