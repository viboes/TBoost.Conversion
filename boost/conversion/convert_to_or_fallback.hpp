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
 \file
 \brief
 Defines the free function @c convert_to_or_fallback.

 The @c convert_to_or_fallback function converts the @c from parameter to a @c To type. If the conversion fails the fallback value is used to construct a To @c instance. 
 
 The default implementation applies the conversion @c To operator of the @c From class or
 the copy constructor of the @c To class. When an exception is thrown the falback is returned.
 Of course if both exist the conversion is ambiguous.
 A user adapting another type could need to specialize the @c convert_to_or_fallback free function if the default behavior is not satisfactory.

The user can add the @c convert_to_or_fallback overloading on any namespace found by ADL from the @c Source or the @c Target.
A trick is used to overload on the return type by adding a dummy parameter having the Target.

But sometimes, as it is the case for the standard classes,
we can not add new functions on the std namespace, so we need a different technique.

The technique consists in partially specialize on the function @c convert_to_or_fallback on the @c boost::conversion namespace.
For compilers for which we can not partially specialize a function a trick is used: instead of calling directly to the @c convert_to_or_fallback member function,
@c convert_to_or_fallback calls to the static operation apply on a class with the same name in the namespace @c overload_workaround.
Thus the user can specialize partially this class.
 */

#ifndef BOOST_CONVERSION_CONVERT_TO_HPP
#define BOOST_CONVERSION_CONVERT_TO_HPP

#include <boost/conversion/convert_to.hpp>

namespace boost {
  namespace conversion {
    namespace overload_workaround {
      //! <c>struct convert_to_or_fallback</c> used when overloading can not be applied.
      //! This struct can be specialized by the user.
      template < typename To, typename From, typename Fallback>
      struct convert_to_or_fallback {
        //!
        //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
        //! @Returns the converted value if the conversion suceeds or the fallback.
        //! @NoThows
        inline static To apply(const From& val, Fallback const& fallback)
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
    }

    //! @brief Default @c convert_to_or_fallback overload, used when ADL fails.
    //!
    //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
    //! @Returns the converted value if the conversion suceeds or the fallback.
    //! @NoThows
    //! Forwards the call to the overload workarround, which can yet be specialized by the user for standard C++ types.
    template < typename To, typename From, typename Fallback >
    To convert_to_or_fallback(const From& val, Fallback const& fallback, dummy::type_tag<To> const&) {
      return conversion::overload_workaround::convert_to_or_fallback<To,From>::apply(val, fallback);
    }
  }
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace conversion_impl {
    template <typename Target, typename Source, typename Fallback>
    Target convert_to_or_fallback_impl(Source const& from, Fallback const& fallback) {
      using namespace boost::conversion;
      //use boost::conversion::convert_to_or_fallback if ADL fails
      return convert_to_or_fallback(from, fallback, boost::dummy::type_tag<Target>());
    }
  }
#endif

  //!
  //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
  //! @Returns the converted value if the conversion suceeds or the fallback.
  //! @NoThows
  //!
  //! This function can be partially specialized on compilers supporting it.
  //! A trick is used to partially specialize on the return type by adding a dummy parameter.
  template <typename Target, typename Source, typename Fallback>
  Target convert_to_or_fallback(Source const& from, Fallback const& fallback, boost::dummy::base_tag<Target> const& p=boost::dummy::base_tag<Target>()) {
    (void)p;
    return conversion_impl::convert_to_or_fallback_impl<Target>(from, fallback);
  }

}

#endif

