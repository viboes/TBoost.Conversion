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
 * @brief
 */


#ifndef BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_CONSTRUCTIBLE_HPP


#include <boost/utility/declval.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_all_extents.hpp>
#include <boost/config.hpp>
#if defined(BOOST_NO_DECLTYPE)
#include <boost/typeof/typeof.hpp>
#endif // defined(BOOST_NO_DECLTYPE)

namespace boost {

  namespace detail {

    namespace is_constructible {
      struct any {
        template <typename T>
        any(T);
      };
      template <class T>
      BOOST_TYPEOF_TPL((T(), true_type()))
      test0(T&);
      false_type
      test0(any);

      template <class T, class A1>
      BOOST_TYPEOF_TPL((T(declval<A1>()), true_type()))
      test1(T&, A1&);
      template <class A1>
      false_type
      test1(any, A1&);

      template <class T, class A1, class A2>
      BOOST_TYPEOF_TPL((T(declval<A1>(),declval<A2>()), true_type()))
      test2(T&, A1&, A2&);
      template <class A1, class A2>
      false_type
      test2(any, A1&, A2&);
      template <bool, class T>
      struct imp0 // false, T is not a scalar
          : public common_type
                   <
                   BOOST_TYPEOF_TPL(test1(declval<T&>()))
                   >::type
      {};
      template <bool, class T, class A1>
      struct imp1 // false, T is not a scalar
          : public common_type
                   <
                   BOOST_TYPEOF_TPL(test1(declval<T&>(), declval<A1>()))
                   >::type
      {};
      template <bool, class T, class A1, class A2>
      struct imp2 // false, T is not a scalar
          : public common_type
                   <
                   BOOST_TYPEOF_TPL(test2(declval<T&>(), declval<A1>(), declval<A2>()))
                   >::type
      {};
      template <class T>
      struct imp0<true, T>
          : public is_scalar<T>
          {};

      template <class T, class A1>
      struct imp1<true, T, A1>
          : public is_convertible<A1, T>
          {};

      template <class T, class A1, class A2>
      struct imp2<true, T, A1, A2>
          : public false_type
          {};
      template <bool, class T>
      struct void_check0
          : public imp0<is_scalar<T>::value || is_reference<T>::value,
                                      T>
          {};

      template <bool, class T, class A1>
      struct void_check1
          : public imp1<is_scalar<T>::value || is_reference<T>::value,
                                      T, A1>
          {};

      template <bool, class T, class A1, class A2>
      struct void_check2
          : public imp2<is_scalar<T>::value || is_reference<T>::value,
                                      T, A1, A2>
          {};

      template <class T>
      struct void_check0<true, T>
          : public false_type
          {};

      template <class T, class A1>
      struct void_check1<true, T, A1>
          : public false_type
          {};

      template <class T, class A1, class A2>
      struct void_check2<true, T, A1, A2>
          : public false_type
          {};

      struct nat {};

      template <class A>
      struct imp0<false, A[]>
          : public false_type
          {};

      template <class A, class A1>
      struct imp1<false, A[], A1>
          : public false_type
          {};

      template <class A, class A1, class A2>
      struct imp2<false, A[], A1, A2>
          : public false_type
          {};

    }
  }

  template <class T, class A1 = detail::is_constructible::nat,
                     class A2 = detail::is_constructible::nat>
  struct is_constructible
      : public detail::is_constructible::void_check2<is_void<T>::value
                                            || is_abstract<T>::value
                                            || is_function<T>::value
                                            || is_void<A1>::value
                                            || is_void<A2>::value,
                                               T, A1, A2>
      {};

  template <class T>
  struct is_constructible<T, detail::is_constructible::nat, detail::is_constructible::nat>
      : public detail::is_constructible::void_check0<is_void<T>::value
                                            || is_abstract<T>::value
                                            || is_function<T>::value,
                                               T>
      {};

  template <class T, class A1>
  struct is_constructible<T, A1, detail::is_constructible::nat>
      : public detail::is_constructible::void_check1<is_void<T>::value
                                            || is_abstract<T>::value
                                            || is_function<T>::value
                                            || is_void<A1>::value,
                                               T, A1>
      {};
  namespace detail {
    namespace is_constructible {
      template <class A, std::size_t N>
      struct imp0<false, A[N]>
          : public boost::is_constructible<typename remove_all_extents<A>::type>
          {};

      template <class A, std::size_t N, class A1>
      struct imp1<false, A[N], A1>
          : public false_type
          {};

      template <class A, std::size_t N, class A1, class A2>
      struct imp2<false, A[N], A1, A2>
          : public false_type
          {};
    }
  }
}


#endif

