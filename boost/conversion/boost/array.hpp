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
  namespace conversion {

    /**
     * Partial specialization of @c converter for @c boost::array of the same size
     */
    template < typename Target, typename Source, std::size_t N>
    struct converter< array<Target,N>, array<Source,N> >
    {
      //! @Returns the array having as elements the result of the conversion of each one of the source array elements.
      inline array<Target,N> operator()(array<Source,N> const & from)
      {
        array<Target,N> to;
        boost::conversion::assign_to(to, from);
        return to;
      }
    };
    /**
     * Partial specialization of @c assigner for @c boost::array of the same size
     */
    template < typename Target, typename Source, std::size_t N>
    struct assigner< array<Target,N>, array<Source,N> >
    {
      //! @Effects assign to each one of the target array elements the conversion of the source array element.
      array<Target,N>& operator()(array<Target,N>& to, array<Source,N> const & from)
      {
        for (unsigned int i =0; i<N; ++i)
        {
            to[i]=boost::conversion::convert_to<Target>(from[i]);
        }
        return to;
      }
    };
  }

  #ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  //! @brief @c convert_to overloading for source and target been @c boost::array of the same size.
  //!
  //! @Effects converts each one of the source array elements and store the result in the corresponding index on the target array.
  //! @Returns The @c to parameter reference.
  template < typename Target, typename Source, std::size_t N>
  inline array<Target,N>& assign_to(array<Target,N>& to, array<Source,N> const & from)
  {
    return conversion::assigner<array<Target,N>, array<Source,N> >()(to, from);
  }
  #endif
}

#endif

