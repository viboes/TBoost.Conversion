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

#include <boost/conversion/type_traits/boost/array.hpp>
#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <algorithm>
#include <boost/config.hpp>
#include <boost/conversion/is_extrinsically_assignable.hpp>
#include <boost/conversion/type_traits/is_copy_assignable.hpp>
#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/is_extrinsically_convertible.hpp>
#include <boost/conversion/type_traits/is_explicitly_convertible.hpp>


namespace boost {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  //! trick to generate the doc. Don't take care of it
  struct trick_array{};
#endif

  namespace conversion {

    /**
     * Partial specialization of @c implicit_converter for @c boost::array of the same size
     *
     * !!!!!!!!!!!! boost::array is not constructible frome array<U,N> so this should be removed or replaced by explicit
     */
    template < typename Target, typename Source, std::size_t N>
    struct implicit_converter_cp< array<Target,N>, array<Source,N>
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(
        ExtrinsicallyAssignable<Target,Source>
        )
#else
        , typename enable_if_c<
        is_extrinsically_assignable<Target, Source>::value
        >::type
#endif
    > : true_type
    {
      //! @Returns the array having as elements the result of the conversion of each one of the source array elements.
      inline array<Target,N> operator()(array<Source,N> const & from)
      {
        array<Target,N> to;
        //boost::conversion::assign_to(to, from);
        for (unsigned int i =0; i<N; ++i)
        {
            boost::conversion::assign_to(to[i], from[i]);
        }
        return to;
      }
    };

    /**
     * Partial specialization of @c assigner for @c boost::array of the same size
     */
    template < typename Target, typename Source, std::size_t N>
    struct assigner_cp< array<Target,N>, array<Source,N>
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(
        ExtrinsicallyAssignable<Target,Source>
  && ! Assignable<Target, Source>
        )
#else
        , typename enable_if_c<
        is_extrinsically_assignable<Target,Source>::value
  && ! is_assignable<Target, Source>::value
        >::type
#endif
    > : true_type
    {
      //! @Effects assign to each one of the target array elements the conversion of the source array element.
      array<Target,N>& operator()(array<Target,N>& to, array<Source,N> const & from)
      {
        for (unsigned int i =0; i<N; ++i)
        {
            boost::conversion::assign_to(to[i], from[i]);
        }
        return to;
      }
    };
    /**
     * Partial specialization of @c assigner for @c boost::array of the same size
     */
    template < typename Target, typename Source, std::size_t N>
    struct assigner_cp< array<Target,N>, array<Source,N>
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requites(
        ExtrinsicallyAssignable<Target,Source>
     && Assignable<Target, Source>
        )
#else
        , typename enable_if_c<
        is_extrinsically_assignable<Target,Source>::value
     && is_assignable<Target, Source>::value
        >::type
#endif
    > : true_type
    {
      //! @Effects assign to each one of the target array elements the conversion of the source array element.
      array<Target,N>& operator()(array<Target,N>& to, array<Source,N> const & from)
      {
        for (unsigned int i =0; i<N; ++i)
        {
            to[i] = from[i];
        }
        return to;
      }
    };
  }

#if defined(BOOST_CONVERSION_DOUBLE_CP)
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  //! @brief @c assign_to overloading for source and target been @c boost::array of the same size.
  //!
  //! @Effects converts each one of the source array elements and store the result in the corresponding index on the target array.
  //! @Returns The @c to parameter reference.
  template < typename Target, typename Source, std::size_t N>
  inline array<Target,N>& assign_to(array<Target,N>& to, array<Source,N> const & from)
  {
    return conversion::assigner<array<Target,N>, array<Source,N> >()(to, from);
  }
#endif
#endif
}

#endif

