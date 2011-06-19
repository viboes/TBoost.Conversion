//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BOOST_CONVERSION_DETAIL_IS_OPTIONAL_HPP
#define BOOST_CONVERSION_DETAIL_IS_OPTIONAL_HPP

#include <boost/optional.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost {

  namespace conversion {
    namespace detail {
      template <typename T>
      struct is_optional : false_type {};
      template <typename T>
      struct is_optional< ::boost::optional<T> > : true_type {};

    }
  }
}

#endif

