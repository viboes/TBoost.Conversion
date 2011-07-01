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
 * @brief Defines the free function @c explicit_convert_to and its customization point @c explicit_converter.
 *
 *  The @c explicit_convert_to function explicit converts the @c from parameter to a @c Target type.
 *
 */
#ifndef BOOST_CONVERSION_EXPLICIT_CONVERT_TO_HPP
#define BOOST_CONVERSION_EXPLICIT_CONVERT_TO_HPP
#if defined(BOOST_CONVERSION_DOUBLE_CP)
/**
 *  A user adapting another type could need to overload the @c explicit_convert_to free function
 *  if the default behavior is not satisfactory.
 *  The user can add the @c explicit_convert_to overloading on any namespace found by ADL from the @c Source or the @c Target.
 *  A trick is used to overload on the return type by adding a dummy parameter having the Target.
 *
 *  But sometimes, as it is the case for the standard classes,
 *  we can not add new functions on the @c std namespace, so we need a different technique.
 *  In this case the user can partially specialize the @c boost::conversion::overload_workaround::explicit_convert_to struct.
 *
 */
#endif


#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/conversion/type_traits/is_explicitly_convertible.hpp>
#include <boost/conversion/type_traits/is_extrinsic_convertible.hpp>
#include <boost/conversion/detail/is_optional.hpp>
#include <boost/optional.hpp>

namespace boost {
  namespace conversion {

    template <typename Target, typename Source>
    Target
    explicit_convert_to(Source const& from);


#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR) || defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    //! Customization point for @c explicit_convert_to.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! This class must be specialized by the user when the default behavior of @c explicit_converter is not satisfying.
    template < typename Target, typename Source, class Enable = void >
    struct explicit_converter_cp : false_type {};

    //! Default @c explicit_converter.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! The default implementation relies on the @c explicit_converter_cp which must be specialized by the user.
    template < typename Target, typename Source, class Enable = void >
    struct explicit_converter : explicit_converter_cp<Target,Source,Enable> {};

    //! Specialization for @c explicit_converter when @c is_explicitly_convertible<Source,Target>.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Requires @c is_explicitly_convertible<Source,Target>
    template < typename Target, typename Source >
    struct explicit_converter<Target, Source,
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        requires(ExplicitConvertible<Source,Target>)
#else
        typename enable_if_c<
          is_explicitly_convertible<Source,Target>::value
          && !(detail::is_optional<Target>::value && !detail::is_optional<Source>::value)
        >::type
#endif
    > : true_type
    {
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c Target operator of the @c Source class throws.
      Target operator()(const Source& val)
      {
        return Target((val));
      }
    };
    //! Specialization for @c explicit_converter when @c is_explicitly_convertible<Source,Target>.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Requires @c is_extrinsic_convertible<Source,Target>
    template < typename Target, typename Source >
    struct explicit_converter<Target, Source,
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        requires(ExtrinsicConvertible<Source,Target>)
#else
        typename enable_if_c<
                is_extrinsic_convertible<Source,Target>::value
            && !is_explicitly_convertible<Source,Target>::value
            && !(detail::is_optional<Target>::value && !detail::is_optional<Source>::value)
        >::type
#endif
              > : true_type
    {
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c Target operator of the @c Source class throws.
      Target operator()(const Source& val)
      {
        return implicit_convert_to<Target>(val);
      }
    };

    //! @brief @c explicit converter specialization to try to convert the source to @c Target::value_type when @c Target is optional.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Requires @c is_extrinsic_explicit_convertible<Source,Target>
    //! We can see this specialization as a try_convert_to function.
    template < class Target, class Source>
    struct explicit_converter< optional<Target>, Source,
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        requires(ExtrinsicExplicitConvertible<Source,Target>)
#else
     typename enable_if_c<
        explicit_converter<Target,Source>::value
        && ! detail::is_optional<Source>::value
      >::type
#endif
    > : true_type

    {
      //! @Returns If the source is convertible to the target @c value_type
      //! @c Target initialized to the result of the conversion.
      //! Uninitialized  @c Target otherwise.
      optional<Target> operator()(Source const & from)
      {
        try
        {
          return optional<Target>(explicit_convert_to<Target>(from));
        }
        catch (...)
        {
          return optional<Target>();
        }
      }
    };
#else
    //! Customization point for @c explicit_convert_to.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    template < typename Target, typename Source, class Enable = void >
    struct explicit_converter_cp : false_type
    {
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c Target operator of the @c Source class throws.
      Target operator()(const Source& val)
      {
        return Target((val));
      }
    };

    namespace detail {
    template < typename Target, typename Source, bool TargetIsOptional, bool SourceIsOptional>
    struct explicit_converter_aux : explicit_converter_cp<Target, Source>
    {};
    //! @brief @c explicit converter specialization to try to convert the source to @c Target::value_type when @c Target is optional.
    //!
    //! We can see this specialization as a try_convert_to function.
    template < class Target, class Source>
    struct explicit_converter_aux< optional<Target>, Source, true, false> : true_type

    {
      //! @Returns If the source is convertible to the target @c value_type
      //! @c Target initialized to the result of the conversion.
      //! Uninitialized  @c Target otherwise.
      optional<Target> operator()(Source const & from)
      {
        try
        {
          return optional<Target>(explicit_convert_to<Target>(from));
        }
        catch (...)
        {
          return optional<Target>();
        }
      }
    };
    }
    //! Default @c explicit_converter.
    template < typename Target, typename Source, class Enable = void >
    struct explicit_converter : detail::explicit_converter_aux<Target,Source,detail::is_optional<Target>::value, detail::is_optional<Source>::value> {};



#endif


#if defined(BOOST_CONVERSION_DOUBLE_CP)
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c explicit_convert_to overload, used when ADL fails.
      //!
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using by default the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c Target operator of the @c Source class or the copy constructor of the @c Target class throws.
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename Target, typename Source >
      Target explicit_convert_to(const Source& from, dummy::type_tag<Target> const&)
      {
        return conversion::explicit_converter<Target,Source>()(from);
      }
    }

    namespace impl {
      template <typename Target, typename Source>
      Target explicit_convert_to_impl(Source const& from)
      {
        using namespace boost::conversion::impl_2;
        //use boost::conversion::impl_2::explicit_convert_to if ADL fails
        return explicit_convert_to(from, dummy::type_tag<Target>());
      }
    }
#endif
#endif

    //! @brief Extrinsic conversion function.
    //! Converts the @c from parameter to an instance of the @c Target type.
    //! This function can be seen as an emulation of free function overload of the conversion operator.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Params
    //! @Param{source,source of the conversion}
    //!
    //! @Returns The result of @c explicit_converter customization point.
    //! @Throws  Whatever the @c explicit_converter call operator throws.
    //!
    template <typename Target, typename Source>
    Target
    explicit_convert_to(Source const& from)
    {
#if defined(BOOST_CONVERSION_DOUBLE_CP)
      return boost::conversion::impl::explicit_convert_to_impl<Target>(from);
#else
      return conversion::explicit_converter<Target,Source>()(from);
#endif
    }



  }
}

#endif

