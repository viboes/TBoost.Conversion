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
 * @brief Defines the type trait @c is_extrinsically_explicit_convertible.
 */

#ifndef BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_HPP
#define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_HPP


#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
namespace boost {
  namespace conversion {
    /**
     * States if @c Source is extrinsically explicit convertible to @c Target.
     *
     * Condition: @c true_type if and only if the return expression in the following code
     * would be well-formed:
     * @code
     *   Target test() { return explicit_convert_to<Target>(declval<Source>()); }
     * @endcode
     *
     * @Requires @c Target and @c Source must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
     *
     */
    template <typename Source, typename Target>
    struct is_extrinsically_explicit_convertible_tagged {};

  //! Macro stating if the compiler doesn't support the features needed to define the @c is_extrinsically_explicit_convertible type trait for classes.
  #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED

  }
}
#else


#include <boost/conversion/config.hpp>
#include <boost/conversion/detail/any.hpp>
#include <boost/conversion/detail/yes_no_types.hpp>
#include <boost/conversion/detail/dummy_size.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/utility/declval.hpp>
#include <boost/conversion/type_traits/is_convertible.hpp>

#if ! defined BOOST_NO_DECLTYPE
  #if defined _MSC_VER
    #if ! defined BOOST_NO_SFINAE_EXPR
#error
      #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_SIZEOF
    #else
      #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED
    #endif
  #elif defined __clang__
#error
    #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_DECLTYPE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 7 )
       #if ! defined BOOST_NO_SFINAE_EXPR
         #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_SIZEOF
       #else
         #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED
       #endif
     #else
       #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED
       //#define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_DECLTYPE
     #endif
  #else
#error
       #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_DECLTYPE
  #endif
#elif ! defined BOOST_NO_SFINAE_EXPR
  #if defined __clang__
    #error
    #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_SIZEOF
  #elif defined __GNUC__
    #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_SIZEOF
  #else
    #error
    #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_SIZEOF
  #endif
#else
  #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED
#endif

#if ! defined BOOST_NO_RVALUE_REFERENCES
  #if defined _MSC_VER
  #elif defined __clang__
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_RVALUE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
     #else
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_RVALUE
     #endif
  #else
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_RVALUE
  #endif
#endif

namespace boost {
  namespace conversion {
  namespace impl_2 {}
    namespace detail {
      namespace is_extrinsically_explicit_convertible_tagged {
        using namespace boost::conversion::impl_2;

    template <typename S, typename T,
    bool True =
           (is_void<S>::value && is_void<T>::value)
        || ((is_scalar<T>::value || is_reference<T>::value) && is_convertible<S,T>::value)
    ,
    bool False =
           (is_void<S>::value && !is_void<T>::value)
        || (!is_void<S>::value && is_void<T>::value)
        || is_abstract<T>::value
        || is_function<T>::value
        >
    struct imp;

#if defined BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_DECLTYPE
    template <typename S, typename T>
    struct imp<S,T,false,false>
    {
      template <typename S1, typename T1>
      static decltype((
          explicit_convert_to(declval<S1>(), conversion::dummy::type_tag<T1>()) // EXPR
          , true_type()))
      #if defined BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_RVALUE
      selector(S1&&, T1&&);
      #else
      selector(S1&, T1&);
      #endif

      template <typename S1, typename T1>
      static false_type
      selector(any,any);

      typedef typename common_type<decltype(selector(declval<S>(), declval<T>()))>::type type;
    };

#elif defined BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED_USES_SIZEOF

    template <typename S, typename T>
    struct imp<S,T,false,false>
    {
      template<typename S1, typename T1>
      static yes_type
      selector(
        dummy_size<
          sizeof(
            explicit_convert_to(declval<S1>(), conversion::dummy::type_tag<T1>()) // EXPR
          )
        >*
      );

      template<typename S1, typename T1>
      static no_type
      selector(...);

      static const bool value =
        sizeof(selector<S,T>(0)) ==
        sizeof(yes_type);
      typedef boost::integral_constant<bool,value> type;
    };

#else
    template <typename S, typename T>
    struct imp<S,T,false,false>
    : public conversion::explicit_converter<T,S> {};
#endif
    template <typename S, typename T, std::size_t N>
    struct imp<S[N],T[N],false,false>
    : public false_type {};
    template <typename S, typename T, std::size_t N>
    struct imp<S[N],T,false,false>
    : public false_type {};
    template <typename S, typename T, std::size_t N>
    struct imp<S,T[N],false,false>
    : public false_type {};
    template <typename S, typename T>
    struct imp<S[],T[],false,false>
    : public false_type {};
    template <typename S, typename T>
    struct imp<S[],T,false,false>
    : public false_type {};
    template <typename S, typename T>
    struct imp<S,T[],false,false>
    : public false_type {};

    template <typename S,typename T,bool B>
    struct imp<S, T, true,B>
        : public true_type {};

    template <typename S,typename T,bool B>
    struct imp<S, T, B,true>
        : public false_type {};

      } // is_extrinsically_explicit_convertible_tagged
    } // detail


  template <typename Source, typename Target>
  struct is_extrinsically_explicit_convertible_tagged
      : public detail::is_extrinsically_explicit_convertible_tagged::imp<Source, Target> {};

} // conversion
} // boost

#endif // doc

#endif // header

