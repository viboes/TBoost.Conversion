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

#if defined(BOOST_CONVERSION_DOUBLE_CP)
/**
 *  A user adapting specific types could need to specialize the @c try_convert_to free function if the default behavior is not satisfactory or if the specialization can perform better.

 *  A user adapting another type could need to overload the @c try_convert_to free function
 *  if the default behavior is not satisfactory.
 *  The user can add the @c try_convert_to overloading on any namespace found by ADL from the @c Source or the @c Target.
 *  A trick is used to overload on the return type by adding a dummy parameter having the Target.
 *
 *  But sometimes, as it is the case for the standard classes,
 *  we can not add new functions on the @c std namespace, so we need a different technique.
 *  In this case the user can partially specialize the @c boost::conversion::overload_workaround::try_convert_to struct.
*/
#endif


#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/boost/optional.hpp>

namespace boost {
  namespace conversion {
    //! Customization point for @c try_convert_to.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! This struct can be specialized by the user.
    template < typename Target, typename Source, class Enable = void >
    struct try_converter {
      //! @Requires @c Target must be CopyConstructible and @c ::boost::conversion::convert_to<Target>(from) must be well formed.
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

#if defined(BOOST_CONVERSION_DOUBLE_CP)
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c try_convert_to overload, used when ADL fails.
      //!
      //! @Effects  Converts the @c from parameter to an instance of the @c Target type, using by default the conversion operator or copy constructor.
      //! @NoThrow
      //! @Returns A optional<Target> uninitialized when conversion fails.
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename Target, typename Source >
      optional<Target> try_convert_to(const Source& from, dummy::type_tag<Target> const&) {
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
#endif

    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Effects  Converts the @c from parameter to an instance of the @c Target type, using by default the conversion operator or copy constructor.
    //! @NoThrow
    //! @Returns A optional<Target> uninitialized when conversion fails.
    template <typename Target, typename Source>
    optional<Target> try_convert_to(Source const& from) {
#if defined(BOOST_CONVERSION_DOUBLE_CP)
      return boost::conversion::impl::try_convert_to_impl<Target>(from);
#else
      return conversion::try_converter<Target,Source>()(from);
#endif
    }
  }

}

#endif

