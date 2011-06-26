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


#ifndef BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_HPP
#define BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_HPP

#include <boost/conversion/assign_to.hpp>

namespace boost {

  /**
   * trait-type that is @c true_type when @c Target is extrinsic assignable from @c Source.
   */
  template <class Target, class Source>
  struct is_extrinsic_assignable : conversion::assigner<Target, Source> {};

}


#endif

