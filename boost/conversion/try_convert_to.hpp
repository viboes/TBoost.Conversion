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
 Defines the free function @c try_convert_to.

 The @c try_convert_to function converts the @c from parameter to a @c To type and returns an optional<To>, uninitialized if conversion fails.
 
 The default implementation applies the conversion @c To operator of the @c From class or
 the copy constructor of the @c To class on a try-catch block and returns optional with the converted value if succeeds and an uninitialized optional otherwise.
 Of course if both exist the conversion is ambiguous.
 A user adapting specific types could need to specialize the @c try_convert_to free function if the default behavior is not satisfactory or if the specialization can perform better.

The user can add the @c try_convert_to overloading on any namespace found by ADL from the @c Source or the @c Target.
A trick is used to overload on the return type by adding a dummy parameter having the Target.

But sometimes, as it is the case for the standard classes,
we can not add new functions on the std namespace, so we need a different technique.

The technique consists in partially specialize on the function @c try_convert_to on the @c boost::conversion namespace.
For compilers for which we can not partially specialize a function a trick is used: instead of calling directly to the @c try_convert_to member function,
@c try_convert_to calls to the static operation apply on a class with the same name in the namespace @c overload_workaround.
Thus the user can specialize partially this class.
 */

#ifndef BOOST_CONVERSION_TRY_CONVERT_TO_HPP
#define BOOST_CONVERSION_TRY_CONVERT_TO_HPP

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/boost/optional.hpp>

namespace boost {
  namespace conversion {
    namespace overload_workaround {
#if 0
      //! @brief @c convert_to specialization to try to convert the source to @c Target::value_type when @c Target is optional.
      //!
      //! We can see this specialization as a try_convert_to function.
      template < class Target, class Source>
      struct convert_to< optional<Target>, Source>
      {
        //! @Returns If the source is convertible to the target @c value_type
        //! @c Target initialized to the result of the conversion.
        //! Uninitialized  @c Target otherwise.
        inline static optional<Target> apply(Source const & from)
        {
          try
          {
            return optional<Target>(boost::conversion::convert_to<Target>(from));
          }
          catch (...)
          {
            return optional<Target>();
          }
        }
      };
#endif
      //! <c>struct try_convert_to</c> used when overloading can not be applied.
      //! This struct can be specialized by the user.
      template < typename To, typename From >
      struct try_convert_to {
        //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
        //! @NoThrow
        //! @Returns A optional<Ratget> uninitialized when conversion fails.
        inline static optional<To> apply(const From& val)
        {
          try 
          {
            return make_optional(boost::conversion::convert_to<To>(val));
          } 
          catch (...)
          {
            return optional<To>();
          }
        }
      };
    }

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace impl_2 {

    //! @brief Default @c try_convert_to overload, used when ADL fails.
    //!
    //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
    //! @NoThrow
    //! @Returns A optional<Target> uninitialized when conversion fails.
    //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
    template < typename To, typename From >
    optional<To> try_convert_to(const From& val, dummy::type_tag<To> const&) {
      return conversion::overload_workaround::try_convert_to<To,From>::apply(val);
    }
  }
  namespace impl {
    template <typename Target, typename Source>
    optional<Target> try_convert_to_impl(Source const& from) {
      using namespace boost::conversion::impl_2;
      //use boost::conversion::try_convert_to if ADL fails
      return try_convert_to(from, dummy::type_tag<Target>());
    }
  }
#endif


  //!
  //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
  //! @NoThrow
  //! @Returns A optional<Target> uninitialized when conversion fails.
  //!
  //! This function can be overloaded by the user for specific types.
  //! A trick is used to partially specialize on the return type by adding a dummy parameter.
  template <typename Target, typename Source>
  optional<Target> try_convert_to(Source const& from, dummy::base_tag<Target> const& p=dummy::base_tag<Target>()) {
    (void)p;
    return boost::conversion::impl::try_convert_to_impl<Target>(from);
  }
  }

}

#endif

