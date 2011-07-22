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

#ifndef BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_HPP
#define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_HPP


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
    template <class Source, class Target>
    struct is_extrinsically_explicit_convertible {};

  //! Macro stating if the compiler doesn't support the features needed to define the @c is_extrinsically_explicit_convertible type trait for classes.
  #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE

  }
}
#else


#include <boost/config.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/utility/declval.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/conversion/explicit_convert_to.hpp>

#if ! defined BOOST_NO_DECLTYPE
  #if defined _MSC_VER
    #if ! defined BOOST_NO_SFINAE_EXPR
      #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_SIZEOF
    #else
      #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE
    #endif
  #elif defined __clang__
    #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_DECLTYPE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
       #if ! defined BOOST_NO_SFINAE_EXPR
         #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_SIZEOF
       #else
         #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE
       #endif
     #else
       #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_DECLTYPE
     #endif
  #else
       #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_DECLTYPE
  #endif
#elif ! defined BOOST_NO_SFINAE_EXPR
  #define BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_SIZEOF
  #if defined __clang__
  #elif defined __GNUC__
  #endif
#else
  #define BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE
#endif

#if ! defined BOOST_NO_RVALUE_REFERENCES
  #if defined _MSC_VER
  #elif defined __clang__
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_RVALUE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
     #else
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_RVALUE
     #endif
  #else
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_RVALUE
  #endif
#endif

namespace boost {
  namespace conversion {
  namespace detail_is_extrinsically_explicit_convertible {
    struct any {
      template <typename T>
      any(T);
    };
    //! type useful to compare with the sizeof
    typedef char yes_type;
    //! type useful to compare with the sizeof
    struct no_type { char a[2]; };

    //! type useful to accept a sizeof as parameter
    template<std::size_t N>
    struct dummy;

    template <class U>
    struct test
    {
        U u;
    };
    template <class T, class S, bool BothVoid = is_void<T>::value && is_void<S>::value, bool BothNonVoid = !is_void<T>::value && !is_void<S>::value >
    struct imp;
#if defined BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_DECLTYPE

    template <class T, class S>
    decltype((boost::conversion::explicit_convert_to<T>(declval<test<S> >()), true_type()))
    #if defined BOOST_CONVERSION_TT_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_RVALUE
    selector(T&&, S&&);
    #else
    selector(T&, S&);
    #endif

    false_type
    selector(any);

    template <class T, class S>
    struct imp<T,S,false,true>
    : public common_type<decltype(selector(declval<T>(), declval<S>()))>::type {};

#elif defined BOOST_CONVERSION_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_USES_SIZEOF

    template <class T, class S>
    struct imp<T,S,false,true>
    {
      template<class X, class Y>
      static detail_is_extrinsically_explicit_convertible::yes_type
      selector(detail_is_extrinsically_explicit_convertible::dummy<sizeof(boost::conversion::explicit_convert_to<X>(
          declval<Y>()))>*);

      template<class X, class Y>
      static detail_is_extrinsically_explicit_convertible::no_type
      selector(...);

      static const bool value =
                sizeof(selector<T,S>(0)) == sizeof(detail_is_extrinsically_explicit_convertible::yes_type);
      typedef boost::integral_constant<bool,value> type;
    };

#else
    template <class T>
    struct imp<T,S,false,true>
    : public false_type {};
#endif
    template <class T,class S>
    struct imp<T, S, true,false>
        : public true_type {};

    template <class T,class S>
    struct imp<T, S, false,false>
        : public false_type {};

  }


  template <class Source, class Target>
  struct is_extrinsically_explicit_convertible
      : public detail_is_extrinsically_explicit_convertible::imp<Source, Target> {};

  template <class T>
  struct is_extrinsically_explicit_convertible<fusion::void_,T> : false_type {};
}
}

#endif // doc

#if 0
#include <boost/fusion/tuple.hpp>

namespace boost {
  namespace conversion {

  template <class Source, class Target>
  struct is_extrinsically_explicit_convertible : conversion::explicit_converter<Target, Source> {};
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  template <class T>
  struct is_extrinsically_explicit_convertible<fusion::void_,T> : false_type {};
  template <>
  struct is_extrinsically_explicit_convertible<void, void> : true_type {};
  template <>
  struct is_extrinsically_explicit_convertible<const void,void> : true_type {};
  template <>
  struct is_extrinsically_explicit_convertible<void, const void> : true_type {};
  template <>
  struct is_extrinsically_explicit_convertible<const void, const void> : true_type {};
#endif

  }
}
#endif


#endif

