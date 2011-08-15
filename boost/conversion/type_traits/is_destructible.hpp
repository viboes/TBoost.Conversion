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
 * @brief Defines the type trait @c is_destructible.
 */

#ifndef BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_HPP

#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
namespace boost {
  /**
   * States if @c T is destructible.
   *
   * @Condition: @c true_type if and only if given:
   *
   * @code
   *   template <typename U>
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
   *
   * @Remark
   *   - On compilers providing an intrinsic for this trait, the intrinsic will be used.
   *   - On C++0x mode, @c std::is_destructible will be used when available.
   *   - On compilers supporting SFINAE_EXPR or DECLTYPE the library provided a valid implementation.
   *   - Otherwise,
   *     - the library will provide specialization for the builtin types in this file,
   *     - the library will provide specialization for specific standard types in the associated @c type_traits/std/file.hpp
   *     - the library will provide specialization for specific boost types in the associated @c type_traits/boost/file.hpp
   *     - the user will need to provide other specific specializations.
   */
  template <typename T>
  struct is_destructible
  {};

  //! Macro stating if the compiler doesn't support the features needed to define the @c is_destructible type trait for classes.
  #define BOOST_CONVERSION_NO_IS_DESTRUCTIBLE

}
#else


#include <boost/config.hpp>
#include <boost/conversion/type_traits/detail/any.hpp>
#include <boost/conversion/type_traits/detail/yes_no_types.hpp>
#include <boost/conversion/type_traits/detail/dummy_size.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/utility/declval.hpp>

#if ! defined BOOST_NO_DECLTYPE
  #if defined _MSC_VER
      #define BOOST_CONVERSION_NO_IS_DESTRUCTIBLE
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
  namespace type_traits {
    namespace detail {
      namespace is_destructible {
    template <typename U>
    struct test
    {
        U u;
    };
    template <typename T, bool False = is_void<T>::value || is_abstract<T>::value, bool True = is_scalar<T>::value >
    struct imp;
#if defined BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_DECLTYPE

    template <typename T>
    decltype((declval<test<T> >().~test<T>(), true_type()))
    #if defined BOOST_CONVERSION_TT_IS_DESTRUCTIBLE_USES_RVALUE
    selector(T&&);
    #else
    selector(T&);
    #endif

    false_type
    selector(any);

    template <typename T>
    struct imp<T,false,false>
    : public common_type<decltype(selector(declval<T>()))>::type {};

#elif defined BOOST_CONVERSION_IS_DESTRUCTIBLE_USES_SIZEOF

    template <typename T>
    struct imp<T,false,false>
    {
      template<typename X>
      static yes_type
      selector(dummy_size<sizeof(declval<test<T> >().~test<T>(),int())>*);

      template<typename X>
      static no_type
      selector(...);

      static const bool value =
                sizeof(selector<T>(0)) == sizeof(yes_type);
      typedef boost::integral_constant<bool,value> type;
    };

#else
    template <typename T>
    struct imp<T,false,false>
    : public false_type {};
#endif
    template <typename T, bool IsScalar>
    struct imp<T, true, IsScalar>
        : public false_type {};
    template <typename T>
    struct imp<T, false, true>
        : public true_type {};

      }
    }
  }
  template <typename T>
  struct is_destructible
      : public type_traits::detail::is_destructible::imp<T> {};

  /**
   * @c is_destructible specialization for reference types.
   *
   * Condition: references are always destructible.
   */
  template <typename T>
  struct is_destructible<T&> : true_type {};
  /**
   * @c is_destructible specialization for unbound arrays.
   *
   * Condition: unbound arrays are no destructible.
   */
  template <typename A>
  struct is_destructible<A[]> : false_type {};
  /**
   * @c is_destructible specialization for bound arrays.
   *
   * Condition: is_destructible<A>.
   */
  template <typename A, std::size_t N>
  struct is_destructible<A[N]> : is_destructible<A> {};

}


#endif // doc
#endif // header

