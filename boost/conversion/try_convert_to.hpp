//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/*!
 @file
 @brief
 Defines the free function @c try_convert_to and its customization point @c try_converter.

 The @c try_convert_to function converts the @c from parameter to a @c Target type and returns an optional<Target>, uninitialized if conversion fails.
 
 */

#ifndef BOOST_CONVERSION_TRY_CONVERT_TO_HPP
#define BOOST_CONVERSION_TRY_CONVERT_TO_HPP

#include <boost/conversion/config.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/boost/optional.hpp>
#include <boost/conversion/is_extrinsically_explicit_convertible.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
  namespace conversion  {
    //! Customization point for @c try_convert_to.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! This class must be specialized by the user when the default behavior of @c try_convert_to is not satisfying.
    template < typename Target, typename Source, typename Enable = void >
    struct try_converter_cp : false_type {};

    //! Default @c try_converter.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! The default implementation relies on the @c try_converter_cp which must be specialized by the user.
    template < typename Target, typename Source, typename Enable = void >
    struct try_converter : try_converter_cp<Target,Source,Enable> {};

    //! Specialization for @c try_converter when @c is_extrinsically_explicit_convertible<Source,Target>.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Requires @c is_extrinsically_explicit_convertible<Source,Target>
    template < typename Target, typename Source>
    struct try_converter<Target, Source,
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        requires(ExtrinsicallyExplicitConvertible<Source,Target>)
#else
        typename enable_if_c<
          is_extrinsically_explicit_convertible<Source,Target>::value
        >::type
#endif
    > : true_type
    {
      //! @Requires @c ::boost::conversion::convert_to<Target>(from) must be well formed.
      //! @Effects  Converts the @c from parameter to an instance of the @c Target type, using by default the conversion operator or copy constructor.
      //! @NoThrow
      //! @Returns A optional<Ratget> uninitialized when conversion fails.
      optional<Target> operator()(const Source& val)
      {
        try
        {
          return make_optional(boost::conversion::convert_to<Target>(val));
        }
        catch (...)
        {
          return optional<Target>();
        }
      }
    };

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c try_convert_to overload, used when ADL fails.
      //!
      //! @Effects  Converts the @c from parameter to an instance of the @c Target type, using by default the conversion operator or copy constructor.
      //! @NoThrow
      //! @Returns A optional<Target> uninitialized when conversion fails.
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename Target, typename Source >
      typename enable_if_c<
        conversion::try_converter<Target,Source>::value
      , optional<Target> >::type
      try_convert_to(const Source& from, dummy::type_tag<Target> const&) {
        return conversion::try_converter<Target,Source>()(from);
      }
    }
    namespace impl {
      template <typename Target, typename Source>
      optional<Target> try_convert_to_impl(Source const& from) {
        using namespace boost::conversion::impl_2;
        //use boost::conversion::impl_2::try_convert_to if ADL fails
        return try_convert_to(from, dummy::type_tag<Target>());
      }
    }
#endif
  }
}

#include <boost/conversion/detail/is_extrinsically_try_convertible_tagged.hpp>

namespace boost {
  namespace conversion {

    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Effects  Converts the @c from parameter to an instance of the @c Target type, using the @c tyr_converter customization point.
    //! @NoThrow
    //! @Returns A optional<Target> uninitialized when conversion fails.
    //! @Example
    //! @code
    //! optional<Target> t;
    //! Source s;
    //! res=boost::conversion::try_convert_to<Target>(s);
    //! @endcode
    template <typename Target, typename Source>
    typename enable_if_c<
      is_extrinsically_try_convertible_tagged<Source,Target>::value
    , optional<Target> >::type
    try_convert_to(Source const& from) {
      return boost::conversion::impl::try_convert_to_impl<Target>(from);
    }
  }
}

#endif

