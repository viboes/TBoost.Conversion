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
 Defines the free function @c assign_to and its customization point @c assigner.

The function @c assign_to assigns the @c from parameter to the @c to parameter.

 */
#ifndef BOOST_CONVERSION_ASSIGN_TO_HPP
#define BOOST_CONVERSION_ASSIGN_TO_HPP
#if defined(BOOST_CONVERSION_DOUBLE_CP)
/**
A user adapting another type could need to specialize the @c assign_to free function if the default behavior is not satisfactory.
The user can add the @c assign_to overloading on the namespace of the Source or Target classes.
But sometimes as it is the case for the standard classes, we can not add new functions on the std namespace,
so we need a different technique. The technique consists in partially specialize on the function @c assign_to on
the @c boost::conversion::overload_workaround namespace.

 */
#endif

#include <boost/conversion/config.hpp>


#include <cstddef> //for std::size_t
#include <boost/conversion/config.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/conversion/type_traits/is_copy_assignable.hpp>
#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_extrinsic_convertible.hpp>
#include <boost/conversion/type_traits/is_extrinsic_explicit_convertible.hpp>

namespace boost {
  namespace conversion {


#if defined(BOOST_CONVERSION_ENABLE_CND) || defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    //! Customization point for @c assign_to.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! This class must be specialized by the user when the default behavior of @c explicit_converter is not satisfying.
    template < typename Target, typename Source, class Enable = void>
    struct assigner_cp : false_type {};

    //! Default customization point for @c assign_to.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! By default it delegates to the user @c assigner_cp.
    template < typename Target, typename Source, class Enable = void>
    struct assigner : assigner_cp<Target,Source,Enable> {};

    /**
     * Specialization when @c Target is not assignable from @c Source, but @c Target is copy constructible and @c Source is extrinsic convertible to @c Target.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
     * @Requires @c Target must be CopyAssinable and @c @c Source must be extrinsic convertible to @c Target.
     */
    template < typename Target, typename Source>
    struct assigner<Target, Source
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(CopyAssignable<Target>&&ExtrinsicExplicitConvertible<Source,Target>)
#else
        , typename enable_if_c<
          is_copy_assignable<Target>::value
          && is_extrinsic_explicit_convertible<Source,Target>::value
          && ! is_assignable<Target,Source>::value
          >::type
#endif
    > : true_type
    {
      //! @Effects Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
      //! @Throws Whatever the underlying assignment operator of the @c Target class throws.
      Target& operator()(Target& to, const Source& from)
      {
        to = ::boost::conversion::explicit_convert_to<Target>(from);
        return to;
      }
    };
    /**
     * Specialization when @c Target is assignable from @c Source.
     *
     * @tparam Target target type of the conversion.
     * @tparam Source source type of the conversion.
     *
     * @Requires @c Target must be Assinable from Source.
     */

    template < typename Target, typename Source>
    struct assigner<Target,Source
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    , requires(Assignable<Target,Source>)
#else
    , typename enable_if_c<
    is_assignable<Target, Source>::value
    >::type
#endif
    > : true_type
    {
      //! @Effects Assigns the @c from parameter to the @c to parameter.
      //! @Throws  Whatever the underlying assignment operator of the @c Target class throws.
      Target& operator()(Target& to, const Source& from)
      {
        to = from;
        return to;
      }
    };
    
    
    /**
     * Partial specialization for c-array types.
     *
     * @tparam Target target type of the conversion.
     * @tparam Source source type of the conversion.
     * @tparam N the size of the c-arrays.
     *
     * @Requires @c Target must be Assinable from @c Source.
     */
    template < typename Target, typename Source, std::size_t N  >
    struct assigner<Target[N],Source[N]
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    , requires(Assignable<Target,Source>)
#else
    , typename enable_if_c<
      is_assignable<Target, Source>::value
    >::type
#endif
    > : true_type
    {
      //! @Effects  Converts the @c from parameter to the @c to parameter, using by default the assignment operator on each one of the array elements.
      //! @Throws  Whatever the underlying assignment operator of the @c Target class throws.
      //! @Basic
      Target*& operator()(Target(&to)[N], const Source(& from)[N])
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          to[i] = from[i];
        }
        return to;
      }
    };

    /**
     * Partial specialization for c-array types.
     *
     * @tparam Target target type of the conversion.
     * @tparam Source source type of the conversion.
     * @tparam N the size of the c-arrays.
     *
     * @Requires @c Target must be CopyAssinable and @c @c Source must be extrinsic convertible to @c Target.
     */
    template < typename Target, typename Source, std::size_t N  >
    struct assigner<Target[N],Source[N]
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    , requires(CopyAssignable<Target> && ExtrinsicConvertible<Source,Target>)
#else
        , typename enable_if_c<
                                         is_copy_assignable<Target>::value
                                         && is_extrinsic_convertible<Source,Target>::value
                                         && ! is_assignable<Target,Source>::value
        >::type
#endif
    > : true_type
    {
      //! @Effects  Converts the @c from parameter to the @c to parameter, using by default the assignment operator on each one of the array elements.
      //! @Throws  Whatever the underlying assignment operator of the @c Target class throws.
      //! @Basic
      Target*& operator()(Target(&to)[N], const Source(& from)[N])
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          to[i] = ::boost::conversion::implicit_convert_to<Target>(from[i]);
        }
        return to;
      }
    };


#else
    template < typename Target, typename Source, class Enable = void>
    struct assigner_cp :  true_type
    {
      //! @Effects Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
      //! @Throws Whatever the underlying assignment operator of the @c Target class throws.
      Target& operator()(Target& to, const Source& from)
      {
        to = ::boost::conversion::implicit_convert_to<Target>(from);
        return to;
      }
    };
    template < typename Target, typename Source, class Enable = void>
    struct assigner : assigner_cp<Target,Source,Enable> {};

    //! Partial specialization for c-array types.
    //!
    //! @Requires @c Target must be CopyAssinable and @c @c Source must be extrinsic convertible to @c Target.
    template < typename Target, typename Source, std::size_t N  >
    struct assigner<Target[N],Source[N]
    > : true_type
    {
      //! @Effects  Converts the @c from parameter to the @c to parameter, using by default the assignment operator on each one of the array elements.
      //! @Throws  Whatever the underlying assignment operator of the @c Target class throws.
      //! @Basic
      Target*& operator()(Target(&to)[N], const Source(& from)[N])
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          to[i] = ::boost::conversion::implicit_convert_to<Target>(from[i]);
        }
        return to;
      }
    };

#endif


  }

#if defined(BOOST_CONVERSION_DOUBLE_CP)
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
      //use boost::conversion_impl_2::assign_to if ADL fails
      return assign_to(to, from);
    }
  }
#endif
#endif
  namespace conversion {

    //! @brief Extrinsic assign function.
    //! Assigns the @c Source parameter to the @c Target one.
    //! This function can be seen as an emulation of free function overload of the assignment operator.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Params
    //! @Param{to,target of the conversion}
    //! @Param{from,source of the conversion}

    //! @Effects The ones of the assigner customization point.
    //! @Throws  Whatever the assigner customization point throws.

    template <typename Target, typename Source>
    Target& assign_to(Target& to, const Source& from)
    {
#if defined(BOOST_CONVERSION_DOUBLE_CP)
      return boost::conversion_impl::assign_to_impl<Target, Source>(to, from);
#else
      return conversion::assigner<Target,Source>()(to, from);
#endif
    }
  }
}

#endif

