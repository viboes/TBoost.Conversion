//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CA_WRAPPER__HPP
#define BOOST_CA_WRAPPER__HPP

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost { namespace conversion {
    
    template <typename T> 
    class ca_wrapper {
        T& ref_;
    public:
        ca_wrapper(T& r) : ref_(r) {}
        template <typename U>
        operator U() {
            return boost::conversion::convert_to<U>(ref_);
        }
        template <typename U>
        T& operator =(U const& u) {
            return boost::conversion::assign_to(ref_, u);
        }
    };

    template <typename T>
    ca_wrapper<T> mca(T& r) {
        return ca_wrapper<T>(r);
    }
    
}}

#endif

