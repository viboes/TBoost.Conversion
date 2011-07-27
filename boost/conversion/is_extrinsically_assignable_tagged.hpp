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
 * @brief Defines the type trait @c is_extrinsically_assignable_tagged.
 */

#ifndef BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_HPP
#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_HPP

#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
namespace boost {
  namespace conversion {
    /**
     * States if @c Source is extrinsically assignable to @c Target.
     *
     * Condition: @c true_type if and only if the return expression in the following code
     * would be well-formed:
     * @code
     *   Target test() { return implicit_convert_to<Target>(declval<Source>()); }
     * @endcode
     *
     * @Requires @c Target and @c Source must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
     *
     */
    template <class Source, class Target>
    struct is_extrinsically_assignable_tagged {};

  //! Macro stating if the compiler doesn't support the features needed to define the @c is_extrinsically_assignable type trait for classes.
  #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE_TAGGED

  }
}
#else


#include <boost/conversion/config.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_function.hpp>

#include <boost/utility/declval.hpp>
#include <boost/conversion/assign_to.hpp>


#if ! defined BOOST_NO_DECLTYPE
  #if defined _MSC_VER
    #if ! defined BOOST_NO_SFINAE_EXPR
#error
      #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_SIZEOF
    #else
      #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE_TAGGED
    #endif
  #elif defined __clang__
#error
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_DECLTYPE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
       #if ! defined BOOST_NO_SFINAE_EXPR
#error
         #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_SIZEOF
       #else
         #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE_TAGGED
       #endif
     #else
       //#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_SIZEOF
       //#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_DECLTYPE
       #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE_TAGGED
     #endif
  #else
#error
    //#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_SIZEOF
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_DECLTYPE
    //#define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE_TAGGED
  #endif
#elif ! defined BOOST_NO_SFINAE_EXPR
  #if defined _MSC_VER
#error
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_SIZEOF
#elif defined __clang__
#error
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_SIZEOF
  #elif defined __GNUC__
    #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE_TAGGED
  #else
#error
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_SIZEOF
  #endif
#else
  #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE_TAGGED
#endif

#if ! defined BOOST_NO_RVALUE_REFERENCES
  #if defined _MSC_VER
  #elif defined __clang__
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_RVALUE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
     #else
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_RVALUE
     #endif
  #else
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_RVALUE
  #endif
#endif

namespace boost {
  namespace conversion {
  namespace detail_is_extrinsically_assignable_tagged {
  using namespace boost::conversion_impl_2;
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

    template <class S, class T,
    bool True =
        (is_void<S>::value && is_void<T>::value)
     || ((is_scalar<T>::value || is_reference<T>::value) && is_assignable<S,T>::value)
     ,
     bool False =
        (is_void<S>::value && !is_void<T>::value)
     || (!is_void<S>::value && is_void<T>::value)
     || is_abstract<T>::value
     || is_function<T>::value        >
    struct imp;

#if defined BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_DECLTYPE
    template <class S, class T>
    struct imp<S,T,false,false>
    {
      template <class S1, class T1>
      static decltype((
          assign_to(declval<S1>(), declval<T1>()) // EXPR
          , true_type()))
      #if defined BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_RVALUE
      selector(S1&&, T1&&);
      #else
      selector(S1&, T1&);
      #endif

      template <class S1, class T1>
      static false_type
      selector(any,any);

      typedef typename common_type<decltype(selector(declval<S>(), declval<T>()))>::type type;
    };

#elif defined BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_TAGGED_USES_SIZEOF

    template <class S, class T>
    struct imp<S,T,false,false>
    {
      template<class X, class Y>
      static detail_is_extrinsically_assignable_tagged::yes_type
      selector(detail_is_extrinsically_assignable_tagged::dummy<
          sizeof(
              assign_to(declval<S1>(), declval<T1>()) // EXPR
          )
          >*);

      template<class X, class Y>
      static detail_is_extrinsically_assignable_tagged::no_type
      selector(...);

      static const bool value =
        sizeof(selector<S,T>(0)) ==
        sizeof(detail_is_extrinsically_assignable_tagged::yes_type);
      typedef boost::integral_constant<bool,value> type;
    };

#else
    template <class S,class T>
    struct imp<S,T,false,false>
    : public conversion::assigner<T,S> {};
#endif
//    template <class S, class T, std::size_t N>
//    struct imp<S[N],T[N],false,false>
//    : public false_type {};
//    template <class S, class T, std::size_t N>
//    struct imp<S[N],T,false,false>
//    : public false_type {};
//    template <class S, class T, std::size_t N>
//    struct imp<S,T[N],false,false>
//    : public false_type {};
//    template <class S, class T>
//    struct imp<S[],T[],false,false>
//    : public false_type {};
//    template <class S, class T>
//    struct imp<S[],T,false,false>
//    : public false_type {};
//    template <class S, class T>
//    struct imp<S,T[],false,false>
//    : public false_type {};

    template <class S,class T,bool B>
    struct imp<S, T, true,B>
        : public true_type {};

    template <class S,class T,bool B>
    struct imp<S, T, B,true>
        : public false_type {};

  } // detail


  template <class Source, class Target>
  struct is_extrinsically_assignable_tagged
      : public detail_is_extrinsically_assignable_tagged::imp<Source, Target> {};

} // conversion
} // boost

#endif // doc

#endif // header

