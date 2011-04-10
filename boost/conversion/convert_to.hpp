//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/*!
 \file
 \brief
 Defines the free function @c convert_to.

 The @c convert_to function converts the @c from parameter to a @c To type. The default implementation applies the conversion @c To operator of the @c From class or
 the copy constructor of the @c To class.
 Of course if both exist the conversion is ambiguous.
 A user adapting another type could need to specialize the @c convert_to free function if the default behavior is not satisfactory.

The user can add the @c convert_to overloading on any namespace found by ADL from the @c Source or the @c Target.
A trick is used to overload on the return type by adding a dummy parameter having the Target.

But sometimes, as it is the case for the standard classes,
we can not add new functions on the std namespace, so we need a different technique.

The technique consists in partially specialize on the function @c convert_to on the @c boost::conversion namespace.
For compilers for which we can not partially specialize a function a trick is used: instead of calling directly to the @c convert_to member function,
@c convert_to calls to the static operation apply on a class with the same name in the namespace @c partial_specializationworkaround.
Thus the user can specialize partially this class.
 */

#ifndef BOOST_CONVERSION_CONVERT_TO_HPP
#define BOOST_CONVERSION_CONVERT_TO_HPP

namespace boost {
  namespace dummy {
    template <typename T> struct base_tag {  };
    template <typename T> struct type_tag : public base_tag<T> {};
  }
  namespace conversion {
    namespace partial_specialization_workaround {
      template < typename To, typename From >
      struct convert_to {
        inline static To apply(const From& val)
        {
          return To((val));
        }
      };
    }

    template < typename To, typename From >
    To convert_to(const From& val, dummy::type_tag<To> const&) {
      return conversion::partial_specialization_workaround::convert_to<To,From>::apply(val);
    }
  }
  namespace conversion_impl {
    template <typename Target, typename Source>
    Target convert_to_impl(Source const& from) {
      using namespace boost::conversion;
      //use boost::conversion::convert_to if ADL fails
      return convert_to(from, boost::dummy::type_tag<Target>());
    }
  }

  //!
  //! @Effects  Converts the @c from parameter to an instance of the @c To type, using by default the conversion operator or copy constructor.
  //! @Throws  Whatever the underlying conversion @c To operator of the @c From class or the copy constructor of the @c To class throws.
  //! This function can be partialy specialized on compilers supporting it. A trick is used to partialy specialize on the return type by adding a dummy parameter.
  template <typename Target, typename Source>
  Target convert_to(Source const& from, boost::dummy::base_tag<Target> const& p=boost::dummy::base_tag<Target>()) {
    (void)p;
    return conversion_impl::convert_to_impl<Target>(from);
  }

}

#endif

