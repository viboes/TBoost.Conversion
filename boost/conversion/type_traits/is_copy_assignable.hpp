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


#ifndef BOOST_CONVERSION_TT_IS_COPY_ASSIGNABLE_HPP
#define BOOST_CONVERSION_TT_IS_COPY_ASSIGNABLE_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost {

  template <class T>
  struct is_copy_assignable : is_assignable<typename remove_reference<T>::type&, typename remove_reference<T>::type const&> {};

}


#endif

