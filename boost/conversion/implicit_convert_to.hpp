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
 * @brief Defines the free function @c implicit_convert_to and its customization
 *  point @c implicit_converter.
 *
 * The @c implicit_convert_to function converts the @c from parameter to a
 *  @c Target type and is intended to be used in a implicit context.
 *
 * The default behavior returns the implicit conversion when @c Source is
 * implicitly convertible to @c Target
 *
 * When the default behavior is not satisfactory or it doesn't takes care of
 *  specific types, the user could customize the behavior of
 *  @c implicit_convert_to in two ways:
 *
 *    - overload the @c implicit_convert_to on any namespace found by ADL from the
 *  @c Source or the @c Target. A trick is used to overload on the return type
 *  by adding a dummy parameter depending on the @c Target.
 *    - partially specialize the @c boost::conversion::implicit_converter_cp struct.
 *
 *  @note As we can not add new functions on the @c std namespace, partial
 *  specialization is the only option in these cases.
 *
 */
#ifndef BOOST_CONVERSION_IMPLICIT_CONVERT_TO_HPP
#define BOOST_CONVERSION_IMPLICIT_CONVERT_TO_HPP

#include <boost/conversion/config.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/conversion/type_traits/is_convertible.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost {
  namespace conversion {

    namespace dummy {
      //! tag used to overload a function returning the parameter @c T.
      //!
      //! @tparam T The wrapped return type.
      //! Users overloading the @c implicit_convert_to function must use this tag.
      template <typename T>
      struct type_tag
      {
        //! The nested type @c type names the template parameter.
        typedef T type;
      };
    }

    //! Customization point for @c implicit_convert_to free function.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! This class can be specialized by the user when the default behavior of
    //! @c implicit_converter doesn't takes care of he specific types.
    template < typename Target, typename Source, typename Enable = void >
    struct implicit_converter_cp : false_type {};

    //! Default customization point for @c implicit_convert_to.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //! @tparam Enable A dummy template parameter that can be used for SFINAE.
    //!
    //! The default implementation relies on the @c implicit_converter_cp which
    //! must be specialized by the user.
    template < typename Target, typename Source, typename Enable = void >
    struct implicit_converter : implicit_converter_cp<Target,Source,Enable> {};


    //! Specialization for @c implicit_converter when
    //! @c is_convertible<Source,Target>.
    //!
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Requires @c is_convertible<Source,Target>
    template < typename Target, typename Source >
    struct implicit_converter<Target, Source
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        , requires(Convertible<Source,Target>)
#else
        , typename enable_if_c< is_convertible<Source,Target>::value >::type
#endif
    > : true_type
    {
      /**
       * @Effects Converts the @c from parameter to an instance of the
       *  @c Target type, using the conversion operator or copy constructor.
       * @Throws Whatever the underlying conversion @c Target operator of the @c Source class throws.
       */
      Target operator()(const Source& val)
      {
        return val;
      }
    };

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {

      //! @brief Default @c implicit_convert_to overload, used when ADL fails.
      //!
      //! @Effects Converts the @c from parameter to an instance of the @c Target type, using by default the conversion operator or copy constructor.
      //! @Throws  Whatever the underlying conversion @c Target operator of the @c Source class or the copy constructor of the @c Target class throws.
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename Target, typename Source >
      typename enable_if_c<
        conversion::implicit_converter<Target,Source>::value
      , Target>::type
      implicit_convert_to(const Source& from,
          dummy::type_tag<Target> const&)
      {
        return conversion::implicit_converter<Target,Source>()(from);
      }
    }

#endif

  } // namespace conversion
} // namespace boost

#include <boost/conversion/detail/is_extrinsically_convertible_tagged.hpp>

namespace boost {
  namespace conversion {

    //! @brief Extrinsic conversion function.
    //! Converts the @c from parameter to an instance of the @c Target type.
    //! This function can be seen as an emulation of free function overload of the conversion operator.
    //! @tparam Target target type of the conversion.
    //! @tparam Source source type of the conversion.
    //!
    //! @Params
    //! @Param{source,source of the conversion}
    //!
    //! @Returns The result of @c implicit_converter customization point.
    //! @Throws  Whatever the @c implicit_converter call operator throws.
    //!
    //! @Example
    //! @code
    //!   Target t;
    //!   Source s;
    //!   t=boost::conversion::implicit_convert_to<Target>(s);
    //! @endcode
    template <typename Target, typename Source>
    typename enable_if_c<
        is_extrinsically_convertible_tagged<Source, Target>::value
    , Target>::type
    implicit_convert_to(const Source& from)
    {
      using namespace boost::conversion::impl_2;
      //use boost::conversion::impl_2::implicit_convert_to if ADL fails
      return implicit_convert_to(from, dummy::type_tag<Target>());
    }
  } // namespace conversion
} // namespace boost

#endif // header

