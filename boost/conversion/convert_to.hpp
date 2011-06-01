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
 * @brief Defines the free function @c convert_to.
 *
 *  The @c convert_to function converts the @c from parameter to a @c To type.
 *  The default implementation applies the conversion @c To operator of the @c From class or
 *  the copy constructor of the @c To class.
 *  Of course if both exist the conversion is ambiguous.
 *
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

#ifndef BOOST_CONVERSION_CONVERT_TO_HPP
#define BOOST_CONVERSION_CONVERT_TO_HPP

#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
  namespace conversion {
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

    //! meta-function to state if the parameter is a place_holder
    //!
    //! @tparam T The type to check for.
    //! @tparam Enable A dummy parameter that can be used for SFINAE.

    //! The nested type @c type is a mpl boolean which default to @c mpl::false_.
    //!   Specific specialization would make this meta-function to be @c mpl::true_.
    template <typename T, typename Enabled=void>
    struct enable_functor : mpl::false_ {};

      //! customization point for @convert_to.

      //! @tparam To target type of the conversion.
      //! @tparam From source type of the conversion.
      //! @tparam Enable A dummy parameter that can be used for SFINAE.

    template < typename To, typename From, class Enable = void >
    struct converter {
      //! @Effects Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c To operator of the @c From class or the copy constructor of the @c To class throws.
      To operator()(const From& val)
      {
        return To((val));
      }
    };
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c convert_to overload, used when ADL fails.
      //!
      //! @Effects Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c To operator of the @c From class or the copy constructor of the @c To class throws.
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename To, typename From >
      To convert_to(const From& from, dummy::type_tag<To> const&) {
        return conversion::converter<To,From>()(from);
      }
    }

    namespace impl {
      template <typename Target, typename Source>
      Target convert_to_impl(Source const& from) {
        using namespace boost::conversion::impl_2;
        //use boost::conversion::convert_to if ADL fails
        return convert_to(from, dummy::type_tag<Target>());
      }
    }
#endif

    //! @brief Extrinsic conversion function.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Params
    //! @Param{source,source of the conversion}
    //!
    //! @Effects Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
    //! @Throws  Whatever the underlying conversion @c To operator of the @c From class or the copy constructor of the @c To class throws.
    //!
    //! This function can be overloaded by the user.
    //! A trick is used to overload on the return type by adding a defaulted dummy parameter.
    //! Specializations must overload on @c dummy::type_tag<Target>
    //!
    //! This function doesn't participate on overload resolution when @c conversion::enable_functor<Source>::type.
    template <typename Target, typename Source>
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    typename disable_if<typename conversion::enable_functor<Source>::type, Target>::type
#else
    Target
#endif
    convert_to(Source const& from) {
      return boost::conversion::impl::convert_to_impl<Target>(from);
    }
  }
}

#endif

