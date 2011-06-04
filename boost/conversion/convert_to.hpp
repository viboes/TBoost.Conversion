//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief Defines the free function @c convert_to and its customization point @c converter.
 *
 *  The @c convert_to function converts the @c from parameter to a @c Target type.
 *  The default implementation of @ converter applies the conversion @c Target operator of the @c Source class or
 *  the copy constructor of the @c Target class.
 *  Of course if both exist the conversion is ambiguous.
 *
 */
#if defined(BOOST_CONVERSION_DOUBLE_CP)
/**
 *  A user adapting another type could need to overload the @c convert_to free function
 *  if the default behavior is not satisfactory.
 *  The user can add the @c convert_to overloading on any namespace found by ADL from the @c Source or the @c Target.
 *  A trick is used to overload on the return type by adding a dummy parameter having the Target.
 *
 *  But sometimes, as it is the case for the standard classes,
 *  we can not add new functions on the @c std namespace, so we need a different technique.
 *  In this case the user can partially specialize the @c boost::conversion::overload_workaround::convert_to struct.
 *
 */
#endif

#ifndef BOOST_CONVERSION_CONVERT_TO_HPP
#define BOOST_CONVERSION_CONVERT_TO_HPP

//#define BOOST_CONVERSION_ENABLE_CND

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/integral_constant.hpp>
#if defined(BOOST_CONVERSION_ENABLE_CND)
#include <boost/conversion/type_traits/is_explicitly_convertible.hpp>
#endif

namespace boost {

  namespace conversion {
#if defined(BOOST_CONVERSION_DOUBLE_CP)
    namespace dummy {
      //! tag used to overload a function returning T.
      //!
      //! @tparam T The wrapped return type.
      //! Users overloading the @c convert_to function must use this tag.
      template <typename T>
      struct type_tag
      {
        //! The nested type @c type names the template parameter.
        typedef T type;
      };
    }
#endif
    //! meta-function to state if the parameter is a place_holder
    //!
    //! @tparam T The type to check for.
    //! @tparam Enable A dummy parameter that can be used for SFINAE.

    //! The nested type @c type is a mpl boolean which default to @c mpl::false_.
    //!   Specific specialization would make this meta-function to be @c mpl::true_.
    template <typename T, typename Enabled=void>
    struct enable_functor : false_type {};

    //! Customization point for @convert_to.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.

#if defined(BOOST_CONVERSION_ENABLE_CND)
    template < typename Target, typename Source, class Enable = void >
    struct converter : false_type {};
    template < typename Target, typename Source >
    struct converter<Target, Source
              , typename enable_if<is_explicitly_convertible<Source,Target> >::type
              > : true_type
    //template < typename Target, typename Source, class Enable = void >
    //struct converter  : true_type
#else
    template < typename Target, typename Source, class Enable = void >
    struct converter  : true_type
#endif
    {
      //! @Requires @c Target must be CopyConstructible from @c Source or @c Source convertible to @c Target
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using by default the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c Target operator of the @c Source class or the copy constructor of the @c Target class throws.
      Target operator()(const Source& val)
      {
        return Target((val));
      }
    };
#if defined(BOOST_CONVERSION_DOUBLE_CP)
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c convert_to overload, used when ADL fails.
      //!
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using by default the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c Target operator of the @c Source class or the copy constructor of the @c Target class throws.
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename Target, typename Source >
      Target convert_to(const Source& from, dummy::type_tag<Target> const&)
      {
        return conversion::converter<Target,Source>()(from);
      }
    }

    namespace impl {
      template <typename Target, typename Source>
      Target convert_to_impl(Source const& from)
      {
        using namespace boost::conversion::impl_2;
        //use boost::conversion::impl_2::convert_to if ADL fails
        return convert_to(from, dummy::type_tag<Target>());
      }
    }
#endif
#endif

    //! @brief Extrinsic conversion function.
    //! Converts the @c from parameter to an instance of the @c Target type.
    //! This function can be seen as an emulation of free function overload of the conversion operator.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Params
    //! @Param{source,source of the conversion}
    //!
    //! @Returns The result of @c converter customization point.
    //! @Throws  Whatever the @c converter call operator throws.
    //!
    //! This function doesn't participate on overload resolution when @c conversion::enable_functor<Source>::type is mpl::true_.
    template <typename Target, typename Source>
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    typename disable_if<typename conversion::enable_functor<Source>::type, Target>::type
#else
    Target
#endif
    convert_to(Source const& from)
    {
#if defined(BOOST_CONVERSION_DOUBLE_CP)
      return boost::conversion::impl::convert_to_impl<Target>(from);
#else
      return conversion::converter<Target,Source>()(from);
#endif
    }
  }
}

#endif

