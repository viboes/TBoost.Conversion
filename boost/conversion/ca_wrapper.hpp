//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CA_WRAPPER_HPP
#define BOOST_CA_WRAPPER_HPP

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
    namespace conversion {

        template <typename T>
        class ca_wrapper {
        public:
            T& ref_;
            ca_wrapper(ca_wrapper const& r) : ref_(r.ref_) { }
            ca_wrapper(T& r) : ref_(r) {}
            template <typename U>
            operator U() {
                return boost::convert_to<U>(ref_);
            }
            ca_wrapper& operator =(ca_wrapper<T> const& u) {
                ref_ = u.ref_;
                return *this;                
            }
            template <typename U>
            ca_wrapper& operator =(ca_wrapper<U> const& u) {
                boost::assign_to(ref_, u.ref_);
                return *this;                
            }
            template <typename U>
            ca_wrapper& operator =(U const& u) {
                boost::assign_to(ref_, u);
                return *this;
            }
        };
    }
    template <typename T>
    conversion::ca_wrapper<T> mca(T& r) {
        return conversion::ca_wrapper<T>(r);
    }

}

#endif

