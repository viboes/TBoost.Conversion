//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO_ARRAY__HPP
#define BOOST_CONVERT_TO_ARRAY__HPP

#include <boost/array.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <algorithm>

namespace boost {

    namespace partial_specialization_workaround {
        template < typename T1, typename T2, std::size_t N>
        struct convert_to< array<T1,N>, array<T2,N> > {
            inline static array<T1,N> apply(array<T2,N> const & from)
            {
                array<T1,N> to;
                boost::assign_to(to, from);
                return to;
            }
        };
        template < typename T1, typename T2, std::size_t N>
        struct assign_to< array<T1,N>, array<T2,N> > {        
            inline static array<T1,N>& apply(array<T1,N>& to, array<T2,N> const & from)
            {
                std::transform(from.begin(), from.end(), to.begin(), boost::convert_to<T1,T2>);
                //for (unsigned int i =0; i<N; ++i) {
                //    to[i]=boost::convert_to<T1>(from[i]);
                //}
                return to;
            }
        };

    }
}

#endif

