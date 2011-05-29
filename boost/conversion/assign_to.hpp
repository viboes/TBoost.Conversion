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
 Defines the free function @c assign_to.

The function @c assign_to assigns the @c from parameter to the @c to parameter.
The default implementation applies the the assignment operator of the @c To class.
A user adapting another type could need to specialize the @c assign_to free function if the default behavior is not satisfactory.

The user can add the @c assign_to overloading on the namespace of the Source or Target classes.
But sometimes as it is the case for the standard classes, we can not add new functions on the std namespace,
so we need a different technique.

The technique consists in partially specialize on the function @c assign_to on the @c boost::conversion namespace.
For compilers for which we can not partially specialize a function a trick is used:
instead of calling directly to the @c assign_to member function, @c assign_to calls to the static operation apply
on a class with the same name in the namespace @c overload_workaround.
Thus the user can specialize partially this class.

 */

#ifndef BOOST_CONVERSION_ASSIGN_TO_HPP
#define BOOST_CONVERSION_ASSIGN_TO_HPP

#include <cstddef> //for std::size_t
#include <boost/conversion/convert_to.hpp>

namespace boost {
  namespace conversion {
    namespace overload_workaround {
      //! struct used when overloading can not be applied.
      template < typename To, typename From >
      struct assign_to
      {
        //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
        //! @Throws  Whatever the underlying the assignment operator of the @c To class throws..
        inline static To& apply(To& to, const From& from)
        {
          to = from;
          return to;
        }
      };
      template < typename To, typename From, std::size_t N  >
      struct assign_to<To[N],From[N]>
      {
        //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator on each one of the array elements.
        //! @Throws  Whatever the underlying the assignment operator of the @c To class throws..
        inline static To*& apply(To(&to)[N], const From(& from)[N])
        {
          for (std::size_t i = 0; i < N; ++i)
          {
            to[i] = boost::conversion::convert_to<To>(from[i]);
          }
          return to;
        }
      };
    }

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c assign_to overload, used when ADL fails.
      //!
      //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
      //! @Throws  Whatever the underlying the assignment operator of the @c To class throws..
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename To, typename From >
      To& assign_to(To& to, const From& from, dummy::type_tag<To> const&)
      {
        return conversion::overload_workaround::assign_to<To,From>::apply(to, from);
      }
    }

    namespace impl {
      template <typename Target, typename Source>
      Target& assign_to_impl(Target& to, const Source& from)
      {
        using namespace boost::conversion::impl_2;
        //use boost::conversion::assign_to if ADL fails
        return assign_to(to, from, dummy::type_tag<Target>());
      }
    }
#endif

    //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
    //! @Throws  Whatever the underlying the assignment operator of the @c To class throws..
    //! This function can be partially specialized on compilers supporting it.
    template <typename Target, typename Source>
    Target& assign_to(Target& to, const Source& from, dummy::base_tag<Target> const& p =dummy::base_tag<Target>())
    {
      (void)p;
      return boost::conversion::impl::assign_to_impl<Target, Source>(to, from);
    }
  }
}

#endif

