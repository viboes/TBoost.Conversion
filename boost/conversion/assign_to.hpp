//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/*!
 @file
 @brief
 Defines the free function @c assign_to.

The function @c assign_to assigns the @c from parameter to the @c to parameter.
The default implementation uses the @c convert_to to convert the source to the target and use the copy assignment of the @c Target class.

A user adapting another type could need to specialize the @c assign_to free function if the default behavior is not satisfactory.
The user can add the @c assign_to overloading on the namespace of the Source or Target classes.
But sometimes as it is the case for the standard classes, we can not add new functions on the std namespace,
so we need a different technique. The technique consists in partially specialize on the function @c assign_to on
the @c boost::conversion::overload_workaround namespace.

 */

#ifndef BOOST_CONVERSION_ASSIGN_TO_HPP
#define BOOST_CONVERSION_ASSIGN_TO_HPP

#include <cstddef> //for std::size_t
#include <boost/conversion/convert_to.hpp>

namespace boost {
  namespace conversion {
    //! Customization point for @assign_to.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    template < typename Target, typename Source, class Enable = void>
    struct assigner
    {
      //! @Requires @c Target must be CopyAssinable and @c ::boost::conversion::convert_to<Target>(from) must be well formed.
      //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
      //! @Throws  Whatever the underlying assignment operator of the @c Target class throws.
      Target& operator()(Target& to, const Source& from)
      {
        to = ::boost::conversion::convert_to<Target>(from);
        return to;
      }
    };

    //! partial specialization for c-array types.
    template < typename Target, typename Source, std::size_t N  >
    struct assigner<Target[N],Source[N],void>
    {
      //! @Effects  Converts the @c from parameter to the @c to parameter, using by default the assignment operator on each one of the array elements.
      //! @Throws  Whatever the underlying assignment operator of the @c Target class throws.
      //! @Basic
      Target*& operator()(Target(&to)[N], const Source(& from)[N])
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          to[i] = ::boost::conversion::convert_to<Target>(from[i]);
        }
        return to;
      }
    };
  }

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace conversion_impl_2 {

    //! @brief Default @c assign_to overload, used when ADL fails.
    //!
    //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
    //! @Throws  Whatever the underlying the assignment operator of the @c Target class throws.
    //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
    template < typename Target, typename Source >
    Target& assign_to(Target& to, const Source& from)
    {
      return conversion::assigner<Target,Source>()(to, from);
    }
  }

  namespace conversion_impl {
    template <typename Target, typename Source>
    Target& assign_to_impl(Target& to, const Source& from)
    {
      using namespace boost::conversion_impl_2;
      //use boost::conversion::assign_to if ADL fails
      return assign_to(to, from);
    }
  }
#endif
  namespace conversion {

    //! @brief Extrinsic assign function.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Params
    //! @Param{to,target of the conversion}
    //! @Param{from,source of the conversion}

    //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
    //! @Throws  Whatever the underlying the assignment operator of the @c Target class throws..
    //! This function can be overloaded by the user.

    template <typename Target, typename Source>
    Target& assign_to(Target& to, const Source& from)
    {
      return boost::conversion_impl::assign_to_impl<Target, Source>(to, from);
    }
  }
}

#endif

