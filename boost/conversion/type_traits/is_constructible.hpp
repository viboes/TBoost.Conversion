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

#if 0

#include <boost/config.hpp>
//#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <cstddef>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/utility/declval.hpp>
#include <utility>
#include <boost/array.hpp>
#include <complex>
#include <vector>
#include <boost/fusion/tuple.hpp>
#ifndef BOOST_IS_CONSTRUCTIBLE_ARITY_MAX
#define BOOST_IS_CONSTRUCTIBLE_ARITY_MAX 3
#endif

namespace boost
{
    namespace type_traits_detail
    {
        template<class T>
        T declval();

        typedef char true_type;
        struct false_type { char a[2]; };

        template<std::size_t N>
        struct dummy;
    }

    template<class T, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_IS_CONSTRUCTIBLE_ARITY_MAX, class A, = void BOOST_PP_INTERCEPT)>
    struct is_constructible;

#ifndef BOOST_NO_SFINAE_EXPR

    #define M1(z,n,t) type_traits_detail::declval<A##n>()

    #define M0(z,n,t)                                                                                   \
    template<class T BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                             \
    struct is_constructible<T BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, A)>                          \
    {                                                                                                   \
        template<class X>                                                                               \
        static type_traits_detail::true_type                                                            \
        test(type_traits_detail::dummy<sizeof(X(BOOST_PP_ENUM(n, M1, ~)))>*);                           \
                                                                                                        \
        template<class X>                                                                               \
        static type_traits_detail::false_type                                                           \
        test(...);                                                                                      \
                                                                                                        \
        static const bool value = sizeof(test<T>(0)) == sizeof(type_traits_detail::true_type);          \
        typedef boost::integral_constant<bool,value> type;                                                          \
    };

    BOOST_PP_REPEAT(BOOST_IS_CONSTRUCTIBLE_ARITY_MAX, M0, ~)
    #undef M0
    #undef M1

#else

    #define M0(z,n,t)                                                                                   \
    template<class T BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                             \
    struct is_constructible<T BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, A)>                          \
      : boost::mpl::false_                                                                              \
    {                                                                                                   \
    };

    BOOST_PP_REPEAT(BOOST_IS_CONSTRUCTIBLE_ARITY_MAX, M0, ~)
    #undef M0

#endif

  template <class A1, class A2, class B1, class B2>
  struct is_constructible< std::pair<A1,A2>, std::pair<B1,B2> >
      : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value >
        {};

#if 0
  template <class T1, class T2, std::size_t N>
  struct is_constructible< boost::array<T1,N>, boost::array<T2,N> >
      : integral_constant<bool, is_constructible<T1,T2>::value  >
        {};
#endif
  template < class Target, class Source>
  struct is_constructible< std::complex<Target>, std::complex<Source> >
      : integral_constant<bool, is_constructible<Target,Source>::value  >
        {};

  template < class T1, class A1, class T2, class A2>
  struct is_constructible< std::vector<T1,A1>, std::vector<T2,A2> >
      : integral_constant<bool, is_constructible<T1,T2>::value  >
        {};

  template <class A1, class A2, class B1, class B2>
  struct is_constructible< fusion::tuple<A1,A2>, fusion::tuple<B1,B2> >
      : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value >
        {};

  template <class A1, class A2, class A3, class B1, class B2, class B3>
  struct is_constructible< fusion::tuple<A1,A2,A3>, fusion::tuple<B1,B2,B3> >
      : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value&& is_constructible<A3,B3>::value >
        {};
}

#else
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
#include <utility>
#include <boost/array.hpp>
#include <complex>
#include <vector>
#include <boost/fusion/tuple.hpp>

namespace boost {

  namespace detail {

    namespace is_constructible {
      struct any {
        template <typename T>
        any(T);
      };
      template <class T>
#if defined(BOOST_NO_DECLTYPE)
      BOOST_TYPEOF_TPL((T(), true_type()))
#else
      decltype((T(), true_type()))
#endif
      test0(T&);
      false_type
      test0(any);

      template <class T, class A1>
#if defined(BOOST_NO_DECLTYPE)
      BOOST_TYPEOF_TPL((T(declval<A1>()), true_type()))
#else
      decltype((T(declval<A1>()), true_type()))
#endif
      test1(T&, A1);
      template <class A1>
      false_type
      test1(any, A1);

      template <class T, class A1, class A2>
#if defined(BOOST_NO_DECLTYPE)
      BOOST_TYPEOF_TPL((T(declval<A1>(),declval<A2>()), true_type()))
#else
      decltype((T(declval<A1>(),declval<A2>()), true_type()))
#endif
      test2(T&, A1, A2);
      template <class A1, class A2>
      false_type
      test2(any, A1, A2);
      template <bool, class T>
      struct imp0 // false, T is not a scalar
          : public common_type
                   <
#if defined(BOOST_NO_DECLTYPE)
          BOOST_TYPEOF_TPL(test0(declval<T&>()))
#else
          decltype(test0(declval<T&>()))
#endif
                   >::type
      {};
      template <bool, class T, class A1>
      struct imp1 // false, T is not a scalar
          : public common_type
                   <
#if defined(BOOST_NO_DECLTYPE)
          BOOST_TYPEOF_TPL(test1(declval<T&>(), declval<A1>()))
#else
          decltype(test1(declval<T&>(), declval<A1>()))
#endif
                   >::type
      {};
      template <bool, class T, class A1, class A2>
      struct imp2 // false, T is not a scalar
          : public common_type
                   <
#if defined(BOOST_NO_DECLTYPE)
          BOOST_TYPEOF_TPL(test2(declval<T&>(), declval<A1>(), declval<A2>()))
#else
          decltype(test2(declval<T&>(), declval<A1>(), declval<A2>()))
#endif
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

  template <class A1, class A2, class B1, class B2>
  struct is_constructible< std::pair<A1,A2>, std::pair<B1,B2>, detail::is_constructible::nat>
      : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value >
        {};

#if 0
  template <class T1, class T2, std::size_t N>
  struct is_constructible< boost::array<T1,N>, boost::array<T2,N> , detail::is_constructible::nat>
      : integral_constant<bool, is_constructible<T1,T2>::value  >
        {};
#endif
  template < class Target, class Source>
  struct is_constructible< std::complex<Target>, std::complex<Source>, detail::is_constructible::nat >
      : integral_constant<bool, is_constructible<Target,Source>::value  >
        {};

  template < class T1, class A1, class T2, class A2>
  struct is_constructible< std::vector<T1,A1>, std::vector<T2,A2> , detail::is_constructible::nat>
      : integral_constant<bool, is_constructible<T1,T2>::value  >
        {};

  template <class A1, class A2, class B1, class B2>
  struct is_constructible< fusion::tuple<A1,A2>, fusion::tuple<B1,B2> >
      : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value >
        {};

  template <class A1, class A2, class A3, class B1, class B2, class B3>
  struct is_constructible< fusion::tuple<A1,A2,A3>, fusion::tuple<B1,B2,B3> >
      : integral_constant<bool, is_constructible<A1,B1>::value && is_constructible<A2,B2>::value&& is_constructible<A3,B3>::value >
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
#endif

