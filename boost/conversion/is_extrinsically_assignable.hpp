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
 * @brief Defines the type trait @c is_extrinsically_assignable.
 */


#ifndef BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_HPP
#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_HPP

#include <boost/conversion/assign_to.hpp>

namespace boost {
  namespace conversion {

  /**
   * States if @c Target is extrinsically assignable from @c Source.
   *
   * Condition: @c true_type if and only if the return expression in the following code
   * would be well-formed:
   * @code
   *   assign_to(declval<Target>(), declval<Source>()); }
   * @endcode
   *
   * @Requires @c Target and @c Source must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
   *
   */
  template <class Target, class Source>
  struct is_extrinsically_assignable : conversion::assigner<Target, Source> {};

  }
}


#endif

