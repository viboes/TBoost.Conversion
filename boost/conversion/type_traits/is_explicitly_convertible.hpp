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
 * @brief Defines the type trait @c is_explicitly_convertible.
 */


#ifndef BOOST_CONVERSION_TT_IS_EXPLICITLY_CONVERTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_EXPLICITLY_CONVERTIBLE_HPP

#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
namespace boost {

  /**
   * States if @c Source is is_explicitly_convertible to @c Target.
   *
   * Condition: @c true_type if and only if the following would be well-formed for
   * some invented function f:
   *
   * Target f() {
   *   return static_cast<Target>(decval<Source>());
   * }
   *
   * @Requires @c Source and @ Target must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
   */
  template < class Source, class Target>
  struct is_explicitly_convertible
  {};

  //! Macro stating if the compiler doesn't support the features needed to define the @c is_explicitly_convertible type trait.
  #define BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE


}
#else
#include <boost/conversion/type_traits/is_constructible.hpp>

#if 0


namespace boost {

  template <class Source, class Target>
  struct is_explicitly_convertible : is_constructible<Target, Source> {};
  template <class Target>
  struct is_explicitly_convertible<void,Target> : false_type {};


}

#else

#include <boost/config.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/utility/declval.hpp>
#include <cstddef>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_all_extents.hpp>


#if ! defined BOOST_NO_DECLTYPE
  #if defined _MSC_VER
    #if ! defined BOOST_NO_SFINAE_EXPR
      #define BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_SIZEOF
    #else
      #define BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE
    #endif
  #elif defined __clang__
    #define BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_DECLTYPE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
       #if ! defined BOOST_NO_SFINAE_EXPR
         #define BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_SIZEOF
       #else
         #define BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE
       #endif
     #else
       #define BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_DECLTYPE
     #endif
  #else
       #define BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_DECLTYPE
  #endif
#elif ! defined BOOST_NO_SFINAE_EXPR
  #define BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_SIZEOF
#else
  #define BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE
#endif

#if defined BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE
//#error
#endif
namespace boost {
  namespace type_traits_detail_is_explicitly_convertible {
        //! type used instead of ... to accept any type
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
  }


  namespace type_traits_detail_is_explicitly_convertible {
#if defined BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_DECLTYPE

    // specific positive test functions
  template <class S, class T>
  decltype((static_cast<T>(declval<S>()), true_type()))
  test(T&, S);

    // specific negative test functions
  template <class S>
  false_type
  test(any, S);

// specialization for NOT void, abstract, function or any of the parameters is void, scalar or reference
// depends on whether static_cast<T>(declval<S>()) is well formed

    template <bool, class S, class T>
    struct imp
      : public common_type<decltype(test(declval<T&>(), declval<S>()))>::type
    {};


#elif defined BOOST_CONVERSION_IS_CONSTRUCTIBLE_USES_SIZEOF

// specialization for void, abstract, function or any of the parameters is void, scalar or reference
// depends on whether static_cast<T>(declval<Args>() ...) is well formed

template<bool, class S, class T>
struct imp
{
    template<class X>
    static type_traits_detail_is_explicitly_convertible::yes_type
    test(type_traits_detail_is_explicitly_convertible::dummy<sizeof(static_cast<X>(declval<S>()))>*);

    template<class X>
    static type_traits_detail_is_explicitly_convertible::no_type
    test(...);

    static const bool value =
              sizeof(test<T>(0)) == sizeof(type_traits_detail_is_explicitly_convertible::yes_type);
    typedef boost::integral_constant<bool,value> type;
};


#else

// specialization for void, abstract, function or any of the parameters is void, scalar or reference when
// the compiler doesn't support any know technique that
// allows to detect if static_cast<Target>(declval<Source>()) is well formed
// always false. The user of the library needs to specialize this trait for its owns types.

template<bool, class S, class T>
struct imp
  : boost::false_type
{
};


#endif


// specialization for scalar or reference: depend on the source is convertible to the target
      template <class S, class T>
      struct imp<true, S, T>
          : public integral_constant<bool,is_constructible<T,S>::value || imp<false,S,T>::value >
          {};

// specialization for NOT void, abstract, function or any of the parameters is void:
      // depends on whether the type is scalar or reference

  template <bool, class S, class T>
  struct void_check
    : public imp<is_scalar<T>::value || is_reference<T>::value,
                              S, T>
    {};


// specialization for void, abstract, function or any of the parameters is void: always false
  template <class S, class T>
  struct void_check<true, S, T>
    : public false_type
  {};


// specialization for unbounded arrays: always false

  template <class S, class A>
  struct imp<false, S, A[]>
    : public false_type
  {};

  }


// defines is_explicitly_convertible, depending on whether T is void, abstract, function or any of the parameters is void
  template <class S, class T>
  struct is_explicitly_convertible
    : public type_traits_detail_is_explicitly_convertible::void_check<is_void<T>::value
              || is_abstract<T>::value  || is_function<T>::value
              || is_void<S>::value,
              S, T>
  {};


}

#endif
#endif
#endif

