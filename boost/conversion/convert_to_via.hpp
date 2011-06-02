//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERSION_CONVERT_TO_VIA_HPP
#define BOOST_CONVERSION_CONVERT_TO_VIA_HPP

#include <boost/conversion/convert_to.hpp>

namespace boost {
  namespace conversion {

    template < typename Target, typename Via, typename Source >
    Target convert_to_via(const Source& val) {
        boost::conversion::convert_to<Target>(boost::conversion::convert_to<Via>(val));
    }

  }
}

#endif

