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
 \file
 \brief
 Include this file when using conversions between @c boost::array<> of convertible types.
 */

#ifndef BOOST_CONVERSION_ARRAY_HPP
#define BOOST_CONVERSION_ARRAY_HPP

#include <boost/array.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <algorithm>
#include <boost/config.hpp>

namespace boost {

  #ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING && ! defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace conversion {
    namespace overload_workaround {
      template < typename T1, typename T2, std::size_t N>
      struct convert_to< array<T1,N>, array<T2,N> >
      {
        inline static array<T1,N> apply(array<T2,N> const & from)
        {
          array<T1,N> to;
          boost::conversion::assign_to(to, from);
          return to;
        }
      };
      template < typename T1, typename T2, std::size_t N>
      struct assign_to< array<T1,N>, array<T2,N> >
      {
        inline static array<T1,N>& apply(array<T1,N>& to, array<T2,N> const & from)
        {
          for (unsigned int i =0; i<N; ++i)
          {
              to[i]=boost::conversion::convert_to<T1>(from[i]);
          }
          return to;
        }
      };
    }
  }
  #else
  //! @brief @c convert_to overloading for source and target been @c boost::array of the same size.
  //!
  //! @Returns the array having as elements the conversion from the source array.
  template < typename T1, typename T2, std::size_t N>
  inline array<T1,N> convert_to(array<T2,N> const & from
                      , boost::dummy::type_tag<array<T1,N> > const&
  )
  {
    array<T1,N> to;
    boost::conversion::assign_to(to, from);
    return to;
  }

  //! @brief @c convert_to overloading for source and target been @c boost::array of the same size.
  //!
  //! @Effects converts each one of the source array elements and store the result in the corresponding index on the target array.
  //! @Returns The @c to parameter reference.
  template < typename T1, typename T2, std::size_t N>
  inline array<T1,N>& assign_to(array<T1,N>& to, array<T2,N> const & from
    , boost::dummy::type_tag<array<T1,N> > const&
  )
  {
    for (unsigned int i =0; i<N; ++i)
    {
      to[i]=boost::conversion::convert_to<T1>(from[i]);
    }
    return to;
  }
  #endif
}

#endif

