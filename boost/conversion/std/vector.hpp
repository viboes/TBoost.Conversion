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
  
#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  template < class T, class A>
  struct is_constructible< std::vector<T,A> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  template < class T, class A>
  struct is_constructible< std::vector<T,A>, std::vector<T,A> > : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  template < class T, class A>
  struct is_assignable< std::vector<T,A>&, std::vector<T,A> const& >  : true_type {};
  template < class T, class A>
  struct is_assignable< std::vector<T,A>, std::vector<T,A> >  : true_type {};
#endif
  
  namespace conversion {

    // std namespace can not be overloaded

    /**
     * Partial specialization of @c converter_cp for @c std::vector of extrinsic convertibles.
     */
    template < class T1, class A1, class T2, class A2>
    struct converter_cp< std::vector<T1,A1>, std::vector<T2,A2>
      BOOST_CONVERSION_REQUIRES((
        is_extrinsic_assignable<T1,T2>::value
      ))
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

#if !defined(BOOST_CONVERSION_ENABLE_CND)
    /**
     * Partial specialization of @c assigner_cp for @c std::vector of extrinsic convertibles.
     */
    template < class T1, class A1, class T2, class A2>
    struct assigner_cp< std::vector<T1,A1>, std::vector<T2,A2>
    BOOST_CONVERSION_REQUIRES((
        is_extrinsic_assignable<T1,T2>::value
    ))
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
#endif

  }
}

#endif

//]
