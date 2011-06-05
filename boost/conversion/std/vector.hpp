//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
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
//#include <boost/conversion/pack.hpp>
#include <boost/conversion/type_traits/is_extrinsic_assignable.hpp>

namespace boost {
  namespace conversion {

    // std namespace can not be overloaded

    template < class T1, class A1, class T2, class A2>
    struct converter< std::vector<T1,A1>, std::vector<T2,A2>
#if defined(BOOST_CONVERSION_ENABLE_CND)
    , typename enable_if_c<
            is_extrinsic_assignable<T1,T2>::value
          //is_extrinsic_assignable< std::vector<T1,A1>, std::vector<T2,A2> >::value
    && ! default_converter_condition< std::vector<T1,A1>, std::vector<T2,A2>>::value
        >::type
#endif
    > : true_type
    {
        std::vector<T1,A1> operator()(std::vector<T2,A2> const & from)
        {
            std::vector<T1,A1> to;
            //boost::conversion::assign_to(to, from);
            to.resize(from.size());
            for (unsigned int i=0; i<from.size(); ++i) {
                boost::conversion::assign_to(to[i], from[i]);
            }
            return to;
        }
    };
#if 0

    template < class T1, class A1, class T2, class A2>
    struct converter< std::vector<T1,A1>,
            //~ typename boost::conversion::result_of::pack2<std::vector<T2,A2> const, A1 const>::type
            //~ boost::fusion::tuple<
            std::pair<
                boost::reference_wrapper<std::vector<T2,A2> const>,
                boost::reference_wrapper<A1 const>
            >
#if defined(BOOST_CONVERSION_ENABLE_CND)
    , typename enable_if_c<
        is_extrinsic_assignable<std::vector<T1,A1> >::value,
                                std::pair<
                                  boost::reference_wrapper<std::vector<T2,A2> const>,
                                  boost::reference_wrapper<A1 const>
                                >

        && ! default_converter_condition< std::vector<T1,A1>,
                                          std::pair<
                                            boost::reference_wrapper<std::vector<T2,A2> const>,
                                            boost::reference_wrapper<A1 const>
                                          > >::value

        >::type
#endif
        > : false_type
    {
        std::vector<T1,A1> operator()(
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
#endif

    template < class T1, class A1, class T2, class A2>
    struct assigner< std::vector<T1,A1>, std::vector<T2,A2>
#if defined(BOOST_CONVERSION_ENABLE_CND)
    , typename enable_if_c<
            is_extrinsic_assignable<T1,T2>::value
            && ! default_assigner_condition< std::vector<T1,A1>, std::vector<T2,A2> >::value
        >::type
#endif
    > : true_type
    {
        std::vector<T1,A1>& operator()(
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

  }
}

#endif

//]
