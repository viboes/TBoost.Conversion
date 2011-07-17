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
 * @brief Defines the type trait @c is_copy_assignable.
 */


#ifndef BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_HPP



#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
namespace boost {
  /**
   * States if @c T is destructible.
   *
   * Condition: @c true_type if and only if given:
   *
   * @code
   *   template <class U>
   *   struct test {
   *     U u;
   *   };
   * @endcode
   *
   * the following statement
   *
   * @code
   *   test<T>::~test();
   * @endcode
   *
   * is well formed;
   *
   * @Requires @c T must be a complete type, (possibly cv-qualified) void, or an array of unknown bound.
   */
  template <class T>
  struct is_destructible;
}
#else


#include <boost/config.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/utility/declval.hpp>

#if ! defined BOOST_NO_DECLTYPE
  #if defined _MSC_VER
    #if ! defined BOOST_NO_SFINAE_EXPR
      #define BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_SIZEOF
    #else
      #define BOOST_CONVERSION_NO_IS_DESTRUCTIBLE
    #endif
  #elif defined __clang__
    #define BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_DECLTYPE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
       #if ! defined BOOST_NO_SFINAE_EXPR
         #define BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_SIZEOF
       #else
         #define BOOST_CONVERSION_NO_IS_DESTRUCTIBLE
       #endif
     #else
       #define BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_DECLTYPE
     #endif
  #else
       #define BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_DECLTYPE
  #endif
#elif ! defined BOOST_NO_SFINAE_EXPR
  #define BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_SIZEOF
  #if defined __clang__
  #elif defined __GNUC__
  #endif
#else
  #define BOOST_CONVERSION_NO_IS_DESTRUCTIBLE
#endif

#if ! defined BOOST_NO_RVALUE_REFERENCES
  #if defined _MSC_VER
  #elif defined __clang__
      #define BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_USES_RVALUE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
     #else
      #define BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_USES_RVALUE
     #endif
  #else
      #define BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_USES_RVALUE
  #endif
#endif

namespace boost {
  namespace type_traits_detail_is_destructible {
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
#if defined BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_DECLTYPE

    template <class T>
    decltype((declval<test<T> >().~test<T>(), true_type()))
    #if defined BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_USES_RVALUE
    selector(T&&);
    #else
    selector(T&);
    #endif

    false_type
    selector(any);

    template <class T, bool = is_void<T>::value || is_abstract<T>::value, bool = is_scalar<T>::value >
    struct imp
    : public common_type<decltype(selector(declval<T>()))>::type {};

#elif defined BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_SIZEOF

    template <class T, bool = is_void<T>::value || is_abstract<T>::value, bool = is_scalar<T>::value >
    struct imp
    {
      template<class X>
      static type_traits_detail_is_destructible::yes_type
      selector(type_traits_detail_is_destructible::dummy<sizeof(declval<test<T> >().~test<T>(),int())>*);

      template<class X>
      static type_traits_detail_is_destructible::no_type
      selector(...);

      static const bool value =
                sizeof(selector<T>(0)) == sizeof(type_traits_detail_is_destructible::yes_type);
      typedef boost::integral_constant<bool,value> type;
    };

#else
    template <class T, bool = is_void<T>::value || is_abstract<T>::value, bool = is_scalar<T>::value >
    struct imp
    : public false_type {};
#endif
    template <class T, bool IsScalar>
    struct imp<T, true, IsScalar>
        : public false_type {};
    template <class T>
    struct imp<T, false, true>
        : public true_type {};

  }
  template <class T>
  struct is_destructible
      : public type_traits_detail_is_destructible::imp<T> {};

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)

  /**
   * @c is_destructible specialization for reference types.
   *
   * Condition: references are always copy assignable.
   */
  template <typename T>
  struct is_destructible<T&> : true_type {};
  template <typename A>
  struct is_destructible<A[]> : false_type {};
  template <typename A, std::size_t N>
  struct is_destructible<A[N]> : is_destructible<A> {};

#endif
}


#endif
#endif

