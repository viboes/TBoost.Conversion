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
 * @brief Defines the free function @c explicit_convert_to and its customization
 * point @c explicit_converter.
 *
 * The @c explicit_convert_to function explicit converts the @c from parameter
 * to a @c Target type.
 *
 * The default behavior returns the explicit conversion operator when @c Source is
 * implicitly convertible to @c Target and the extrinsic implicit conversion when
 * @c Source is extrinsically implicitly convertible to @c Target.
 *
 * When the default behavior is not satisfactory or doesn't takes care of
 *  specific types, the user could customize the behavior of
 *  @c explicit_convert_to in two ways:
 *
 *    - overload the @c explicit_convert_to on any namespace found by ADL from the
 *  @c Source or the @c Target. A trick is used to overload on the return type
 *  by adding a dummy parameter depending on the @c Target.
 *    - partially specialize the @c boost::conversion::explicit_converter_cp struct.
 *
 *  @note As we can not add new functions on the @c std namespace, partial
 *  specialization is the only option in these cases.
 */

#ifndef BOOST_CONVERSION_EXPLICIT_CONVERT_TO_HPP
#define BOOST_CONVERSION_EXPLICIT_CONVERT_TO_HPP

#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/conversion/type_traits/is_explicitly_convertible.hpp>
#include <boost/conversion/is_extrinsically_convertible.hpp>
#include <boost/conversion/detail/is_optional.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost {
  namespace conversion {

    //! Customization point for @c explicit_convert_to.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! This class must be specialized by the user when the default behavior of @c explicit_converter is not satisfying.
    template < typename Target, typename Source, typename Enable = void >
    struct explicit_converter_cp : false_type {};

    //! Default @c explicit_converter.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! The default implementation relies on the @c explicit_converter_cp which must be specialized by the user.
    template < typename Target, typename Source, typename Enable = void >
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
          && !(  detail::is_optional<Target>::value &&
               ! detail::is_optional<Source>::value)
        >::type
#endif
    > : true_type
    {
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c Target operator of the @c Source class throws.
      Target operator()(const Source& val)
      //Target operator()(const Source& val)
      {
        return Target((val));
      }
    };
    //! Specialization for @c explicit_converter when @c is_extrinsically_convertible<Source,Target>.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Requires @c is_extrinsically_convertible<Source,Target>
    template < typename Target, typename Source >
    struct explicit_converter<Target, Source,
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        requires(ExtrinsicallyConvertible<Source,Target>)
#else
        typename enable_if_c<
                is_extrinsically_convertible<Source,Target>::value
            && !is_explicitly_convertible<Source,Target>::value
            && !(  detail::is_optional<Target>::value &&
                 ! detail::is_optional<Source>::value)
        >::type
#endif
              > : true_type
    {
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using the conversion operator or copy constructor.
      //! @Throws  Whatever the expression @c implicit_convert_to<Target>(val) throws.
      Target operator()(const Source& val)
      {
        return implicit_convert_to<Target>(val);
      }
    };


#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c explicit_convert_to overload, used when ADL fails.
      //!
      //! @Effects Converts the @c from parameter to an instance of the @c Target type,
      //! using by explicit_converter customization point.
      //! @Throws  Whatever the expression @c conversion::explicit_converter<Target,Source>()(from) throws.

      template < typename Target, typename Source >
      typename enable_if_c<
        conversion::explicit_converter<Target,Source>::value
      , Target>::type
      explicit_convert_to(const Source& from,
          dummy::type_tag<Target> const&)
      {
        return conversion::explicit_converter<Target,Source>()(from);
      }
    }

#endif

  }
}

#include <boost/conversion/detail/is_extrinsically_explicit_convertible_tagged.hpp>

namespace boost {
  namespace conversion {

    //! @brief Extrinsic conversion function.
    //! Converts the @c from parameter to an instance of the @c Target type.
    //! This function can be seen as an emulation of free function overload of
    //! the conversion operator.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Params
    //! @Param{source,source of the conversion}
    //!
    //! @Returns @c explicit_convert_to(from, dummy::type_tag<Target>()).
    //! @Throws Whatever the @c explicit_convert_to(from, dummy::type_tag<Target>()) throws.
    //!
    //! @Example
    //! @code
    //! Target t;
    //! Source s;
    //! t=boost::conversion::explicit_convert_to<Target>(s);
    //! @endcode
    template <typename Target, typename Source>
    typename enable_if_c<
        is_extrinsically_explicit_convertible_tagged<Source,Target>::value
    , Target>::type
    explicit_convert_to(Source const& from)
    {
      using namespace boost::conversion::impl_2;
      //use boost::conversion::impl_2::explicit_convert_to if ADL fails
      return explicit_convert_to(from, dummy::type_tag<Target>());
    }

    //! @brief @c explicit converter specialization to try to convert the source
    //! to @c Target when the target type is @c optional<Target>.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Requires @c is_extrinsically_explicit_convertible<Source,Target>
    //! @Remarks We can see this specialization as a try_convert_to function.
    template < typename Target, typename Source>
    struct explicit_converter< optional<Target>, Source,
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        requires(ExtrinsicallyExplicitConvertible<Source,Target>)
#else
     typename enable_if_c<
        explicit_converter<Target,Source>::value
        && ! detail::is_optional<Source>::value
      >::type
#endif
    > : true_type

    {
      //! @Returns If the source is convertible to the target @c value_type
      //! @c optional<Target> is initialized to the result of the conversion.
      //! Uninitialized  @c optional<Target> otherwise.
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
}

#endif

