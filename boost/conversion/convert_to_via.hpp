//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO_VIA__HPP
#define BOOST_CONVERT_TO_VIA__HPP

#include <boost/conversion/convert_to.hpp>

namespace boost { namespace conversion {

    template < typename To, typename Via, typename From >
    To convert_to_via(const From& val) {
        boost::convert_to<To>(boost::convert_to<Via>(val));
    }
}}

#endif

