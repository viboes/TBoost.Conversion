//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/*!
 @file
 @brief
 Include this file when using conversions between @c std::vector<> of convertible types.
 */

//[VECTOR_HPP
#ifndef BOOST_CONVERSION_STD_VECTOR_HPP
#define BOOST_CONVERSION_STD_VECTOR_HPP

#include <vector>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/pack.hpp>


namespace boost {
  namespace conversion {

    // std namespace can not be overloaded
    namespace overload_workaround {
        template < class T1, class A1, class T2, class A2>
        struct convert_to< std::vector<T1,A1>, std::vector<T2,A2> > {
            inline static std::vector<T1,A1> apply(std::vector<T2,A2> const & from)
            {
                std::vector<T1,A1> res;
                boost::conversion::assign_to(res, from);
                return res;
            }
        };
        template < class T1, class A1, class T2, class A2>
        struct assign_to< std::vector<T1,A1>, std::vector<T2,A2> > {
            inline static std::vector<T1,A1>& apply(
                std::vector<T1,A1>& to,
                std::vector<T2,A2> const & from)
            {
                to.resize(from.size());
                for (unsigned int i=0; i<from.size(); ++i) {
                    boost::conversion::assign_to(to[i], from[i]);
                }
                return to;
            }
        };

        template < class T1, class A1, class T2, class A2>
        struct convert_to< std::vector<T1,A1>,
                //~ typename boost::conversion::result_of::pack2<std::vector<T2,A2> const, A1 const>::type
                //~ boost::fusion::tuple<
                std::pair<
                    boost::reference_wrapper<std::vector<T2,A2> const>,
                    boost::reference_wrapper<A1 const>
                >
            > {
            inline static std::vector<T1,A1> apply(
                typename boost::conversion::result_of::pack2<std::vector<T2,A2> const, A1 const>::type
                const & pack)
            {
                std::vector<T1,A1> res(fusion::at_c<1>(pack).get());
                boost::conversion::assign_to(res, fusion::at_c<0>(pack).get());
                //std::vector<T1,A1> res(pack.second.get());
                //boost::conversion::assign_to(res, pack.first.get());
                return res;
            }
        };

    }
}}

#endif

//]
