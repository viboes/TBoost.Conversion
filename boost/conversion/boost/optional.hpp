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
 Include this file when using conversions between @c boost::optional<> of convertible types.
 */

//[OPTIONAL_HPP
#ifndef BOOST_CONVERSION_OPTIONAL_HPP
#define BOOST_CONVERSION_OPTIONAL_HPP

#include <boost/conversion/type_traits/boost/optional.hpp>
#include <boost/none.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/detail/is_optional.hpp>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost {
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  //! trick to generate the doc. Don't take care of it
  struct trick_optional{};
#endif
  
  namespace conversion {

    /**
     * Partial specialization of @c converter for boost::optional
     */
    template < class Target, class Source>
    struct converter_cp
    < optional<Target>, optional<Source>
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(
        ExtrinsicallyConvertible<Source,Target>
        )
#elif defined(BOOST_CONVERSION_ENABLE_CND)
        , typename enable_if_c<
        is_extrinsically_convertible<Source,Target>::value
        >::type
#endif
    > : true_type
    {
      //! @Returns If the optional source is initialized @c boost::optional<Target> initialized to the conversion of the optional value.
      //! Uninitialized  @c boost::optional<Target otherwise.
      optional<Target> operator()(optional<Source> const & from)
      {
        return (from?optional<Target>(boost::conversion::implicit_convert_to<Target>(from.get())):optional<Target>());
      }
    };


    //! @brief @c converter specialization to try to convert the source to @c Target::value_type when @c Target is optional.
    //!
    //! We can see this specialization as a try_convert_to function.
    template < class Target, class Source>
    struct converter_cp< optional<Target>, Source
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(
        ExtrinsicallyConvertible<Source,Target>
        && ! Optional<Source>
        )
#elif defined(BOOST_CONVERSION_ENABLE_CND)
        , typename enable_if_c<
        is_extrinsically_convertible<Source,Target>::value
        && ! detail::is_optional<Source>::value
        >::type
#endif
    > : true_type

    {
      //! @Returns If the source is convertible to the target @c value_type
      //! @c Target initialized to the result of the conversion.
      //! Uninitialized  @c Target otherwise.
      optional<Target> operator()(Source const & from)
      {
        try
        {
          return optional<Target>(boost::conversion::implicit_convert_to<Target>(from));
        }
        catch (...)
        {
          return optional<Target>();
        }
      }
    };

    //! @brief @c explicit converter specialization to try to convert the source to @c Target::value_type when @c Target is optional.
    //!
    //! We can see this specialization as a try_convert_to function.
    template < class Target, class Source>
    struct explicit_converter_cp< optional<Target>, Source
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(
        ExtrinsicallyExplicit_convertible<Source,Target>
        && ! Optional<Source>
        )
#elif defined(BOOST_CONVERSION_ENABLE_CND)
        , typename enable_if_c<
        is_extrinsically_explicit_convertible<Source,Target>::value
        && ! detail::is_optional<Source>::value
        >::type
#endif
    > : true_type

    {
      //! @Returns If the source is convertible to the target @c value_type
      //! @c Target initialized to the result of the conversion.
      //! Uninitialized  @c Target otherwise.
      optional<Target> operator()(Source const & from)
      {
        try
        {
          return optional<Target>(boost::conversion::explicit_convert_to<Target>(from));
        }
        catch (...)
        {
          return optional<Target>();
        }
      }
    };

  }

#if defined(BOOST_CONVERSION_DOUBLE_CP)
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  //! @brief @c assign_to overloading for source and target been @c boost::optional.
  //!
  //! @Effects As if <c>to = boost::conversion::implicit_convert_to<optional<Target> >(from)</c>.
  //! @Returns The @c to parameter reference.
  template < class Target, class Source>
  inline optional<Target>& assign_to(optional<Target>& to, const optional<Source>& from)
  {
    to = boost::conversion::implicit_convert_to<optional<Target> >(from);
    return to;
  }
#endif
#endif

}

#endif

//]
