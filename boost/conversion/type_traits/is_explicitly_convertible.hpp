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
   * States if @c Source is is explicitly convertible to @c Target.
   *
   * Condition: @c true_type if and only if the following would be well-formed for
   * some invented function test:
   *
   * @code
   * Target test() {
   *   return static_cast<Target>(declval<Source>());
   * }
   * @endcode
   *
   * @Requires @c Source and @c Target must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
   * @Remark @c is_explicitly_convertible has been removed from the C++0x proposal since
   * <b>N3047 - Fixing is_constructible and is_explicitly_convertible</b>
   * was accepted. The library provides the @c static_cast version when the compiler supports the needed features,
   * otherwise it relies on the @c is_constructible version.
   */
  template < typename Source, typename Target>
  struct is_explicitly_convertible
  {};

  //! Macro stating if the compiler doesn't support the features needed to define the @c is_explicitly_convertible type trait
  //! using the @c static_cast version.
  //! In this case the trait is equivalent to @c is_constructible<Target,Source>.

  #define BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE

}
#else
#include <boost/conversion/type_traits/is_constructible.hpp>

#include <boost/config.hpp>
#include <boost/conversion/type_traits/detail/any.hpp>
#include <boost/conversion/type_traits/detail/yes_no_types.hpp>
#include <boost/conversion/type_traits/detail/dummy_size.hpp>
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
#include <boost/conversion/type_traits/is_constructible.hpp>


#if ! defined BOOST_NO_DECLTYPE
  #if defined _MSC_VER
      #define BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE
  #elif defined __clang__
    #define BOOST_CONVERSION_IS_EXPLICIT_CONVERTIBLE_USES_DECLTYPE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
       #if ! defined BOOST_NO_SFINAE_EXPR
         #define BOOST_CONVERSION_IS_EXPLICIT_CONVERTIBLE_USES_SIZEOF
       #else
         #define BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE
       #endif
     #else
       #define BOOST_CONVERSION_IS_EXPLICIT_CONVERTIBLE_USES_DECLTYPE
     #endif
  #else
       #define BOOST_CONVERSION_IS_EXPLICIT_CONVERTIBLE_USES_DECLTYPE
  #endif
#elif ! defined BOOST_NO_SFINAE_EXPR
  #define BOOST_CONVERSION_IS_EXPLICIT_CONVERTIBLE_USES_SIZEOF
#else
  #define BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE
#endif


namespace boost {
  namespace type_traits {
    namespace detail {
      namespace is_explicitly_convertible {
#if defined BOOST_CONVERSION_IS_EXPLICIT_CONVERTIBLE_USES_DECLTYPE

    // specific positive test functions
  template <typename S, typename T>
  decltype((
      static_cast<T>(declval<S>()), true_type()
      ))
  selector(int);

    // specific negative test functions
  template<typename S, typename T>
  false_type
  selector(...);

// specialization for NOT void, abstract, function or any of the parameters is void, scalar or reference
// depends on whether static_cast<T>(declval<S>()) is well formed

    template <bool, typename S, typename T>
    struct imp
      : public common_type<decltype(selector<S,T>(0))>::type
    {};


#elif defined BOOST_CONVERSION_IS_EXPLICIT_CONVERTIBLE_USES_SIZEOF

// specialization for void, abstract, function or any of the parameters is void, scalar or reference
// depends on whether static_cast<T>(declval<Args>() ...) is well formed

template<bool, typename S, typename T>
struct imp
{
    template<typename S1, typename T1>
    static yes_type
    selector(dummy_size<sizeof(static_cast<T1>(declval<S1>()))>*);

    template<typename S1, typename T1>
    static no_type
    selector(...);

    static const bool value =
              sizeof(selector<S,T>(0)) == sizeof(yes_type);
    typedef boost::integral_constant<bool,value> type;
};


#else

// specialization for void, abstract, function or any of the parameters is void, scalar or reference when
// the compiler doesn't support any know technique that
// allows to detect if static_cast<Target>(declval<Source>()) is well formed
// always false. The user of the library needs to specialize this trait for its owns types.

template<bool, typename S, typename T>
struct imp : ::boost::is_constructible<T, S> {};


#endif


// specialization for scalar or reference: depend on the source is convertible to the target
      template <typename S, typename T>
      struct imp<true, S, T>
          : public integral_constant<bool,::boost::is_convertible<S,T>::value || imp<false,S,T>::value >
          {};

// specialization for NOT void, abstract, function or any of the parameters is void:
      // depends on whether the type is scalar or reference

  template <bool, typename S, typename T>
  struct void_check
    : public imp<
        false //is_scalar<T>::value || is_reference<T>::value
        , S, T>
    {};


// specialization for void, abstract, function or any of the parameters is void: always false
  template <typename S, typename T>
  struct void_check<true, S, T>
    : public false_type
  {};


// specialization for unbounded arrays: always false

  template <typename S, typename A>
  struct imp<false, S, A[]>
    : public false_type
  {};

      }
    }
  }


// defines is_explicitly_convertible, depending on whether T is void, abstract, function or any of the parameters is void
  template <typename S, class T>
  struct is_explicitly_convertible
    : public type_traits::detail::is_explicitly_convertible::void_check<
              is_void<S>::value
              //|| is_abstract<T>::value  || is_function<T>::value
              //|| is_void<T>::value
              , S, T>
  {};


}

#endif // doc
#endif // header

