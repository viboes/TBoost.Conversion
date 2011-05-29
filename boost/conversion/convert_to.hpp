//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
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
      //! base tag used to overload a function returning T.
      template <typename T>
      struct base_tag {
        typedef T type;
      };
      //! tag used to overload a function returning T that takes precedence respect to &c base_tag<T>.
      //!
      //! Users overloading the @c convert_to function must use this tag.
      template <typename T>
      struct type_tag : public base_tag<T> {
        typedef T type;
      };
    }

    //! meta-function to state if the parameter is a place_holder
    //!
    //! The nested type @c type is a mpl boolean which default to @c mpl::false_. Specific specialization would make this meta-function to be @c mpl::true_.
    template <typename T, typename Enabled=void>
    struct enable_functor : mpl::false_ {};

    namespace overload_workaround {
      //! struct used when overloading of @c convert_to function can not be applied.
      template < typename To, typename From >
      struct convert_to {
        //! @Effects Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
        //! @Throws  Whatever the underlying conversion @c To operator of the @c From class or the copy constructor of the @c To class throws.
        inline static To apply(const From& val)
        {
          return To((val));
        }
      };
    }
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c convert_to overload, used when ADL fails.
      //!
      //! @Effects Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c To operator of the @c From class or the copy constructor of the @c To class throws.
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename To, typename From >
      To convert_to(const From& val, dummy::type_tag<To> const&) {
        return conversion::overload_workaround::convert_to<To,From>::apply(val);
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
    //! @Effects Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
    //! @Throws  Whatever the underlying conversion @c To operator of the @c From class or the copy constructor of the @c To class throws.
    //!
    //! This function can be overloaded by the user.
    //! A trick is used to overload on the return type by adding a defaulted dummy parameter
    //!
    //! This function doesn't participate on overload resolution when @c conversion::enable_functor<Source>::type.
    template <typename Target, typename Source>
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    typename disable_if<typename conversion::enable_functor<Source>::type, Target>::type
#else
    Target
#endif
    convert_to(Source const& from, dummy::base_tag<Target> const& p=dummy::base_tag<Target>()) {
      (void)p; // warning removal

      return boost::conversion::impl::convert_to_impl<Target>(from);
    }
  }
}

#endif

