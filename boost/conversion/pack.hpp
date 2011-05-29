//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERSION_PACK_HPP
#define BOOST_CONVERSION_PACK_HPP

#include <boost/ref.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/support/pair.hpp>

/*!
 \file
 \brief
 Defines the pack function.


 The result of the @c pack function is equivalent to a fusion sequence containing @c boost::reference_warpper's
 instead of C++ reference (&) as this are not allowed.

*/

namespace boost {
  namespace conversion {
    namespace result_of {

      //! meta-function getting a @c std::pair of @c boost::reference_warpper's.
      //!
      template <typename T1, typename T2> struct pack2 {
          typedef
          std::pair<
          //~ fusion::tuple<
            boost::reference_wrapper<T1>
          , boost::reference_wrapper<T2>
          > type;
      };
      //! meta-function getting a fusion sequence of @c boost::reference_warpper's.
      //!
      template <typename T1, typename T2, typename T3=fusion::void_> struct pack3 {
          typedef fusion::tuple<
              boost::reference_wrapper<T1>
          , boost::reference_wrapper<T2>
          , boost::reference_wrapper<T3>
          > type;
      };
  }

    //! packs together references.
    //!
    template <typename T1, typename T2>
    typename boost::conversion::result_of::pack2<T1 const, T2 const>::type pack(
            T1 const& t1, T2 const& t2) {
            return std::make_pair
            //~ return boost::fusion::make_tuple
                (boost::cref(t1), boost::cref(t2));
    }

    //! packs together references.
    //!
    template <typename T1, typename T2>
    typename boost::conversion::result_of::pack2<T1 const, T2>::type pack(T1 const& t1, T2 & t2) {
            return std::make_pair
            //~ return boost::fusion::make_tuple
                (boost::cref(t1), boost::ref(t2));
    }

    //! packs together references.
    //!
    template <typename T1, typename T2, typename T3>
    typename boost::conversion::result_of::pack3<T1 const, T2 const, T3 const>::type pack(
            T1 const& t1, T2 const& t2, T3 const& t3) {
            return fusion::make_tuple(boost::cref(t1), boost::cref(t2), boost::cref(t3));
    }

    //! packs together references.
    //!
    template <typename T1, typename T2, typename T3>
    typename boost::conversion::result_of::pack3<T1 const, T2 const, T3>::type pack(
            T1 const& t1, T2 const& t2, T3 & t3) {
            return fusion::make_tuple(boost::cref(t1), boost::cref(t2), boost::ref(t3));
    }

    //! packs together references.
    //!
    template <typename T1, typename T2, typename T3>
    typename boost::conversion::result_of::pack3<T1 const, T2, T3 const>::type pack(
            T1 const& t1, T2 & t2, T3 const& t3) {
            return fusion::make_tuple(boost::cref(t1), boost::ref(t2), boost::cref(t3));
    }

    //! packs together references.
    //!
    template <typename T1, typename T2, typename T3>
    typename boost::conversion::result_of::pack3<T1 const, T2, T3>::type pack(
            T1 const& t1, T2 & t2, T3 & t3) {
            return fusion::make_tuple(boost::cref(t1), boost::ref(t2), boost::ref(t3));
    }

  }
}

#endif

