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
 * @brief Defines the type trait @c is_extrinsically_assignable.
 */

#ifndef BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_HPP
#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_HPP

#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
namespace boost {
  namespace conversion {
    /**
     * States if @c Target is extrinsically assignable from @c Source.
     *
     * Condition: @c true_type if and only if the return expression in the following code
     * would be well-formed:
     * @code
     *   assign_to(declval<Target>(), declval<Source>()); }
     * @endcode
     * @Requires @c Target and @c Source must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
     *
     */
    template <typename Target, typename Source>
    struct is_extrinsically_assignable {};

  //! Macro stating if the compiler doesn't support the features needed to define the @c is_extrinsically_assignable type trait for classes.
  #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE

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
      #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_SIZEOF
    #else
      #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE
    #endif
  #elif defined __clang__
#error
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_DECLTYPE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
       #if ! defined BOOST_NO_SFINAE_EXPR
#error
         #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_SIZEOF
       #else
         #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE
       #endif
     #else
       //#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_SIZEOF
       //#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_DECLTYPE
       #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE
     #endif
  #else
#error
    //#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_SIZEOF
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_DECLTYPE
    //#define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE
  #endif
#elif ! defined BOOST_NO_SFINAE_EXPR
  #if defined _MSC_VER
#error
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_SIZEOF
#elif defined __clang__
    //#define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_SIZEOF
    #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE
  #elif defined __GNUC__
    #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE
  #else
#error
    #define BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_SIZEOF
  #endif
#else
  #define BOOST_CONVERSION_NO_IS_EXTRINSIC_ASSIGNABLE
#endif

#if ! defined BOOST_NO_RVALUE_REFERENCES
  #if defined _MSC_VER
  #elif defined __clang__
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_USES_RVALUE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
     #else
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_USES_RVALUE
     #endif
  #else
      #define BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_USES_RVALUE
  #endif
#endif

namespace boost {
  namespace conversion {
    namespace detail {
      namespace is_extrinsically_assignable {
        template <typename T, typename S,
        bool True =
            (is_void<S>::value && is_void<T>::value)
         || ((is_scalar<T>::value || is_reference<T>::value) && is_assignable<T,S>::value)
         ,
         bool False =
            (is_void<S>::value && !is_void<T>::value)
         || (!is_void<S>::value && is_void<T>::value)
         || is_abstract<T>::value
         || is_function<T>::value        >
        struct imp;

#if defined BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_DECLTYPE
        template <typename T, typename S>
        struct imp<T,S,false,false>
        {
          template <typename T1, typename S1>
          static decltype((
              ::boost::conversion::assign_to(declval<T1>(), declval<S1>()) // EXPR
              , true_type()))
          #if defined BOOST_CONVERSION_TT_IS_EXTRINSIC_ASSIGNABLE_USES_RVALUE
          selector(T1&&, S1&&);
          #else
          selector(T1&, S1&);
          #endif

          template <typename T1, typename S1>
          static false_type
          selector(any,any);

          typedef typename common_type<decltype(selector(declval<T>(), declval<S>()))>::type type;
        };

#elif defined BOOST_CONVERSION_IS_EXTRINSIC_ASSIGNABLE_USES_SIZEOF

        template <typename T, typename S>
        struct imp<T,S,false,false>
        {
          template<typename T1, typename S1>
          static yes_type
          selector(dummy_size<
              sizeof(
                  ::boost::conversion::assign_to(declval<T1>(), declval<S1>()) // EXPR
              )
              >*);

          template<typename T1, typename S1>
          static no_type
          selector(...);

          static const bool value =
            sizeof(selector<T,S>(0)) ==
            sizeof(yes_type);
          typedef boost::integral_constant<bool,value> type;
        };

#else
        template <typename T, typename S>
        struct imp<T,S,false,false>
            : public conversion::is_extrinsically_assignable_tagged<T,S> {};
#endif

        template <typename T, typename S, bool B>
        struct imp<T, S, true, B>
            : public true_type {};

        template <typename T,typename S, bool B>
        struct imp<T, S, B, true>
            : public false_type {};

      } // is_extrinsically_assignable
    } // detail

    template <typename Target, typename Source>
    struct is_extrinsically_assignable
        : public detail::is_extrinsically_assignable::imp<Target, Source> {};

    namespace detail {
      namespace is_extrinsically_assignable {
      template <typename T, typename S, std::size_t N>
        struct imp<T[N],S[N],false,false>
            : public conversion::is_extrinsically_assignable<T,S> {};
        template <typename T, typename S, std::size_t N>
        struct imp<T[N],S,false,false>
            : public false_type {};
        template <typename T, typename S, std::size_t N>
        struct imp<T,S[N],false,false>
            : public false_type {};
        template <typename T, typename S>
        struct imp<T[],S[],false,false>
            : public false_type {};
        template <typename T, typename S>
        struct imp<T[],S,false,false>
            : public false_type {};
        template <typename T, typename S>
        struct imp<T,S[],false,false>
            : public false_type {};
      } // is_extrinsically_assignable
    } // detail
  } // conversion
} // boost

#endif // doc

#endif // header

