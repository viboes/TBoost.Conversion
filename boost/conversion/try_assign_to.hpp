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
 Defines the free function @c try_assign_to and its customization point @c try_assigner.

 The function @c try_assign_to assigns the @c from parameter to the @c to parameter. Return @c true if assignment done and @c false otherwise.

 */

#ifndef BOOST_CONVERSION_TRY_ASSIGN_TO_HPP
#define BOOST_CONVERSION_TRY_ASSIGN_TO_HPP

#include <boost/conversion/config.hpp>
#include <cstddef> //for std::size_t
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/type_traits/is_default_constructible.hpp>
#include <boost/conversion/type_traits/is_copy_constructible.hpp>
#include <boost/conversion/type_traits/is_copy_assignable.hpp>
#include <boost/conversion/is_extrinsically_assignable.hpp>

namespace boost {
  namespace conversion {

    //! Customization point for @c try_assign_to.
  //!
  //! @tparam Target target type of the conversion.
  //! @tparam Source source type of the conversion.
  //! @tparam Enable A dummy template parameter that can be used for SFINAE.
  //!
  //! This class must be specialized by the user when the default behavior of @c try_assign_to is not satisfying.
  template < typename Target, typename Source, typename Enable = void >
  struct try_assigner_cp : false_type {};

  //! Default @c try_converter.
  //!
  //! @tparam Target target type of the conversion.
  //! @tparam Source source type of the conversion.
  //! @tparam Enable A dummy template parameter that can be used for SFINAE.
  //!
  //! The default implementation relies on the @c try_assigner_cp which must be specialized by the user.
  template < typename Target, typename Source, typename Enable = void >
  struct try_assigner : try_assigner_cp<Target,Source,Enable> {};

  //! Specialization for @c try_assigner when @c is_extrinsically_explicit_convertible<Source,Target>.
  //!
  //! @tparam Target target type of the conversion.
  //! @tparam Source source type of the conversion.
  //!
  //! @Requires @c is_extrinsically_explicit_convertible<Source,Target>


    template < typename Target, typename Source >
    struct try_assigner<Target, Source,
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    requires(
        CopyConstructible<Target>
    && CopyAssignable<Target>
    && ExtrinsicallyAssignable<Target,Source>
    )
#else
        typename enable_if_c<
          is_copy_constructible<Target>::value
          && is_copy_assignable<Target>::value
          && is_extrinsically_assignable<Target,Source>::value
        >::type
#endif
    > : true_type
    {
      //! @Requires @c Target must be CopyConstructible and @c ::boost::conversion::assign_to(to, from) must be well formed.
      //! @Effects  Converts the @c from parameter to the @c to parameter, using @c assign_to.
      //! @NoThrow
      //! @Returns whether the assignment succeeded.
      //! @Remarks The parameter to is not updated if the conversion fails.
      bool operator()(Target& to, const Source& from)
      {
        Target rollback((to));
        try
        {
          boost::conversion::assign_to<Target>(to , from);
          return true;
        }
        catch (...)
        {
          to = rollback;
          return false;
        }
      }
    };

    //! specialization for c-arrays
    //!
    template < typename Target, typename Source, std::size_t N  >
    struct try_assigner<Target[N],Source[N],
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        requires(
            DefaultConstructible<Target[N]>
        && ExtrinsicallyAssignable<Target[N],Target[N]>
        && ExtrinsicallyAssignable<Target,Source>
        )
#else
        typename enable_if_c<
          is_default_constructible<Target[N]>::value
          && is_extrinsically_assignable<Target[N],Target[N]>::value
          && is_extrinsically_assignable<Target,Source>::value
        >::type
#endif
    > : true_type
    {
      //! @Effects Converts the @c from parameter to  the @c to parameter, using by default the assignment operator on each vector element.
      //! @NoThrow
      //! @Returns the converted value if success or the fallback when conversion fails.
      bool operator()(Target(&to)[N], const Source(& from)[N])
      {
        Target rollback[N];
        boost::conversion::assign_to<Target>(rollback, to);
        try
        {
          for (std::size_t i = 0; i < N; ++i)
          {
            boost::conversion::assign_to<Target>(to[i] , from[i]);
          }
          return true;
        }
        catch (...)
        {
          boost::conversion::assign_to<Target>(to, rollback);
          return false;
        }
      }
    };

  }

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace conversion_impl_2 {
    //! @brief Default @c try_assign_to overload, used when ADL fails.
    //!
    //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
    //! @NoThrow
    //! @Returns the converted value if success or the fallback when conversion fails.
    //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
    template < typename Target, typename Source >
    typename enable_if_c<
      conversion::try_assigner<Target,Source>::value
    , bool >::type
    try_assign_to(Target& to, const Source& from)
    {
      return conversion::try_assigner<Target,Source>()(to, from);
    }
  }

  namespace conversion_impl {
    template <typename Target, typename Source>
    bool try_assign_to_impl(Target& to, const Source& from)
    {
      using namespace boost::conversion_impl_2;
      //use boost::conversion_impl_2::try_assign_to if ADL fails
      return try_assign_to(to, from);
    }
  }
#endif
}

#include <boost/conversion/detail/is_extrinsically_try_assignable_tagged.hpp>

namespace boost {
  namespace conversion {

    //! @brief try to assign a target from a source
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @Effects  Converts the @c from parameter to  the @c to parameter, using the @c try_assigner customization point.
    //! @NoThrow
    //! @Returns true if the conversion succeeds.
    //! @Example
    //! @code
    //! Target t;
    //! Source s;
    //! bool b = boost::conversion::try_assign_to(t,s);
    //! @endcode
    template <typename Target, typename Source>
    typename enable_if_c<
      is_extrinsically_try_assignable_tagged<Target, Source>::value
    , bool >::type
    try_assign_to(Target& to, const Source& from)
    {
      return conversion_impl::try_assign_to_impl<Target, Source>(to, from);
    }
  }
}

#endif

