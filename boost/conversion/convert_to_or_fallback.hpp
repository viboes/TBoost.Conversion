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
 Defines the free function @c convert_to_or_fallback.

 The @c convert_to_or_fallback function converts the @c from parameter to a @c To type. If the conversion fails the fallback value is used to construct a To @c instance. 
 
 The default implementation applies the conversion @c To operator of the @c From class or
 the copy constructor of the @c To class. When an exception is thrown the fallback is returned.
 Of course if both exist the conversion is ambiguous.
 A user adapting another type could need to specialize the @c convert_to_or_fallback free function if the default behavior is not satisfactory.

 *  A user adapting another type could need to overload the @c convert_to_or_fallback free function
 *  if the default behavior is not satisfactory.
 *  The user can add the @c convert_to_or_fallback overloading on any namespace found by ADL from the @c Source or the @c Target.
 *  A trick is used to overload on the return type by adding a dummy parameter having the Target.
 *
 *  But sometimes, as it is the case for the standard classes,
 *  we can not add new functions on the @c std namespace, so we need a different technique.
 *  In this case the user can partially specialize the @c boost::conversion::overload_workaround::convert_to_or_fallback struct.

 */

#ifndef BOOST_CONVERSION_CONVERT_TO_OR_FALLBACK_HPP
#define BOOST_CONVERSION_CONVERT_TO_OR_FALLBACK_HPP

#include <boost/conversion/convert_to.hpp>

namespace boost {
  namespace conversion {
    //! This struct can be specialized by the user.
    template < typename To, typename From, typename Fallback>
    struct converter_or_fallbacker {
      //!
      //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
      //! @Returns the converted value if the conversion succeeds or the fallback.
      //! @NoThrow
      To operator()(const From& val, Fallback const& fallback)
      {
        try
        {
          return boost::conversion::convert_to<To>(val);
        }
        catch (...)
        {
          return To((fallback));
        }
      }
    };

    #if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c convert_to_or_fallback overload, used when ADL fails.
      //!
      //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
      //! @Returns the converted value if the conversion succeeds or the fallback.
      //! @NoThrow
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename To, typename From, typename Fallback >
      To convert_to_or_fallback(const From& val, Fallback const& fallback, dummy::type_tag<To> const&) {
        return conversion::converter_or_fallbacker<To,From,Fallback>()(val, fallback);
      }
    }

    namespace impl {
      template <typename Target, typename Source, typename Fallback>
      Target convert_to_or_fallback_impl(Source const& from, Fallback const& fallback) {
        using namespace boost::conversion::impl_2;
        //use boost::conversion::convert_to_or_fallback if ADL fails
        return convert_to_or_fallback(from, fallback, dummy::type_tag<Target>());
      }
    }
    #endif

    //!
    //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
    //! @Returns the converted value if the conversion succeeds or the fallback.
    //! @NoThrow
    //!
    //! This function can be partially specialized on compilers supporting it.
    //! A trick is used to partially specialize on the return type by adding a dummy parameter.
    template <typename Target, typename Source, typename Fallback>
    Target convert_to_or_fallback(Source const& from, Fallback const& fallback) {
      return conversion::impl::convert_to_or_fallback_impl<Target>(from, fallback);
    }
  }
}

#endif

