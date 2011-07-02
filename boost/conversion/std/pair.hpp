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
 Include this file when using conversions between @c std::pair<> of convertible types.
 */


//[PAIR_HPP
#ifndef BOOST_CONVERSION_STD_PAIR_HPP
#define BOOST_CONVERSION_STD_PAIR_HPP

#include <boost/conversion/config.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/convert_to.hpp>
#include <utility>


namespace boost {
#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
  //! Specialization for std::pair<T,U> default constructor
  template < class T, class U>
  struct is_constructible< std::pair<T,U> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
  //! Specialization for std::pair<T,U> default copy constructor
  template < class T, class U>
  struct is_constructible< std::pair<T,U>, std::pair<T,U> const& >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
  //! Specialization for std::pair<T,U> assignment operator
  template < class T, class U>
  struct is_assignable< std::pair<T,U>, std::pair<T,U> >  : true_type {};
  //! Specialization for std::pair<T,U> assignment operator
  template < class T, class U>
  struct is_assignable< std::pair<T,U>&, std::pair<T,U> const& >  : true_type {};
#endif
  
  
  namespace conversion {

    // std namespace can not be overloaded

    /**
     * Partial specialization of @c converter_cp for @c std::pair of extrinsic convertibles.
     */
    template < class T1, class T2, class S1, class S2>
    struct converter_cp< std::pair<T1,T2>, std::pair<S1,S2>
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , typename enable_if_c<
          is_extrinsic_convertible<S1,T1>::value
          && is_extrinsic_convertible<S2,T2>::value
        >::type
#elif defined(BOOST_CONVERSION_ENABLE_CND)
        , typename enable_if_c<
          is_extrinsic_convertible<S1,T1>::value
          && is_extrinsic_convertible<S2,T2>::value
        >::type
#endif
    > : true_type
    {
        std::pair<T1,T2> operator()(std::pair<S1,S2> const & from)
        {
            return std::pair<T1,T2>(boost::conversion::implicit_convert_to<T1>(from.first), boost::conversion::implicit_convert_to<T2>(from.second));
        }
    };

#if !defined(BOOST_CONVERSION_ENABLE_CND)
    /**
     * Partial specialization of @c assigner_cp for @c std::pair of extrinsic convertibles.
     */
    template < class T1, class T2, class S1, class S2>
    struct assigner_cp< std::pair<T1,T2>, std::pair<S1,S2>
      BOOST_CONVERSION_REQUIRES((
           is_extrinsic_convertible<S1,T1>::value
        && is_extrinsic_convertible<S2,T2>::value
      ))
    > : true_type
    {
        std::pair<T1,T2>& operator()(std::pair<T1,T2>& to, const std::pair<S1,S2>& from)
        {
            to.first = boost::conversion::implicit_convert_to<T1>(from.first);
            to.second = boost::conversion::implicit_convert_to<T2>(from.second);
            return to;
        }
    };
#endif
  }
}

#endif

//]
