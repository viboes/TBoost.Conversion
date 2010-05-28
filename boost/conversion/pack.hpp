//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERSION_PACK__HPP
#define BOOST_CONVERSION_PACK__HPP

#include <boost/ref.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/at_c.hpp>

namespace boost { namespace conversion {
    

template <typename T1, typename T2>
struct result_of_pack {
    typedef std::pair<
        reference_wrapper<T1>, reference_wrapper<T2>
    > type;
};
    
template <typename T1, typename T2>
typename result_of_pack<T1 const, T2 const>::type pack(
        T1 const& t1, T2 const& t2) {
        return std::make_pair(boost::cref(t1), boost::cref(t2));
}

template <typename T1, typename T2>
typename result_of_pack<T1 const, T2>::type pack(T1 const& t1, T2 & t2) {
        return std::make_pair(boost::cref(t1), boost::ref(t2));
}

}}

#endif

