//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/type_traits for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief Defines the type trait @c is_assignable.
 */

#ifndef BOOST_CONVERSION_TT_IS_ASSIGNABLE_HPP
#define BOOST_CONVERSION_TT_IS_ASSIGNABLE_HPP

#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
namespace boost {

  /**
   * States if the @c Target is assignable from the @c Source.
   *
   * Condition: @c true_type if <c>declval<Target>() = declval<Source>()</c> is well-formed when treated as an
   * unevaluated operand.
   *
   * @Requires @c Target and @c Source must be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
   */
  template < typename Target, typename Source>
  struct is_assignable
  {};
  //! Macro stating if the compiler don't support the features needed to define the @c is_assignable type trait.
  #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
}
#else
#include <boost/config.hpp>
#include <boost/type_traits/intrinsics.hpp>

#if ! defined BOOST_NO_RVALUE_REFERENCES
  #if defined _MSC_VER
  #elif defined __clang__
      #define BOOST_CONVERSION_TT_IS_ASSIGNABLE_USES_RVALUE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
     #else
      #define BOOST_CONVERSION_TT_IS_ASSIGNABLE_USES_RVALUE
     #endif
  #else
      #define BOOST_CONVERSION_TT_IS_ASSIGNABLE_USES_RVALUE
  #endif
#endif

#if defined(BOOST_IS_ASSIGNABLE)
#define BOOST_CONVERSION_IS_ASSIGNABLE_USES_INTRINSICS
#elif ! defined(BOOST_NO_DECLTYPE)
  #if defined _MSC_VER
     #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
  #elif defined __clang__
    //#define BOOST_CONVERSION_IS_ASSIGNABLE_USES_DECLTYPE
    #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
  #elif defined __GNUC__
     #if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
       #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
     #else
       #define BOOST_CONVERSION_IS_ASSIGNABLE_USES_DECLTYPE
     #endif
  #else
  #endif
#elif ! defined BOOST_NO_SFINAE_EXPR
  #if defined _MSC_VER
     #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
  #elif defined __clang__
    #define BOOST_CONVERSION_IS_ASSIGNABLE_USES_SIZEOF
  #elif defined __GNUC__
    #define BOOST_CONVERSION_IS_ASSIGNABLE_USES_SIZEOF
  #else
    #define BOOST_CONVERSION_IS_ASSIGNABLE_USES_SIZEOF
  #endif
#else
  #define BOOST_CONVERSION_NO_IS_ASSIGNABLE
#endif

#if !defined(BOOST_IS_ASSIGNABLE)
#include <boost/utility/enable_if.hpp>
#include <boost/conversion/type_traits/detail/any.hpp>
#include <boost/conversion/type_traits/detail/yes_no_types.hpp>
#include <boost/conversion/type_traits/detail/dummy_size.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/utility/declval.hpp>
#endif // !defined(BOOST_IS_ASSIGNABLE)

// should be always the last #include directive
#include <boost/type_traits/detail/bool_trait_def.hpp>

namespace boost {
#ifndef BOOST_IS_ASSIGNABLE
  namespace type_traits {
    namespace detail {
      namespace is_assignable {
        template <typename T,typename S,
          bool True = false,
          bool False = false >
        struct imp;

#if defined BOOST_CONVERSION_IS_ASSIGNABLE_USES_DECLTYPE

        template <typename T, typename S>
        struct imp<T,S,false,false>
        {
          template <typename T1, typename S1>
          static decltype((
              declval<T1>() = declval<S1>()
              , true_type()))
          selector(int);

          template <typename T1, typename S1>
          static false_type
          selector(...);

          typedef decltype(selector<T,S>(0)) type;
        };

#elif defined BOOST_CONVERSION_IS_ASSIGNABLE_USES_SIZEOF

        template <typename T, typename S>
        struct imp<T,S,false,false>
        {
          template<typename T1, typename S1>
          static yes_type
          selector(dummy_size<
              sizeof(
                  declval<T1>() = declval<S1>()
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
        template <typename T,typename S>
        struct imp<T,S,false,false>
        : public false_type {};

        template <> struct imp< bool&, bool const&, false, false> : true_type  {};

        template <> struct imp< int&, int, false, false > : true_type  {};
        template <> struct imp< int&, int&, false, false > : true_type  {};
        template <> struct imp< int&, int const&, false, false > : true_type  {};
        template <> struct imp< int&, double, false, false > : true_type  {};
        template <> struct imp< int&, short const&, false, false > : true_type {};
        template <> struct imp< short&, int const&, false, false > : true_type  {};
        template <> struct imp< float, int, false, false > : true_type  {};
        template <> struct imp< int, float, false, false > : true_type  {};

        template <> struct imp< char, char, false, false > : true_type  {};
        template <> struct imp< char, unsigned char, false, false > : true_type  {};
        template <> struct imp< char, short, false, false > : true_type  {};
        template <> struct imp< char, unsigned short, false, false > : true_type  {};
        template <> struct imp< char, int, false, false > : true_type  {};
        template <> struct imp< char, unsigned int, false, false > : true_type  {};
        template <> struct imp< char, long, false, false > : true_type  {};
        template <> struct imp< char, unsigned long, false, false > : true_type  {};

        template <> struct imp< char, char const&, false, false > : true_type  {};
        template <> struct imp< char, short const&, false, false > : true_type  {};
        template <> struct imp< char, int const&, false, false > : true_type  {};
        template <> struct imp< char, long const&, false, false > : true_type  {};
        template <> struct imp< char, unsigned char const&, false, false > : true_type  {};
        template <> struct imp< char, unsigned short const&, false, false > : true_type  {};
        template <> struct imp< char, unsigned int const&, false, false > : true_type  {};
        template <> struct imp< char, unsigned long const&, false, false > : true_type  {};

        template <> struct imp< short, char, false, false > : true_type  {};
        template <> struct imp< short, unsigned char, false, false > : true_type  {};
        template <> struct imp< short, short, false, false > : true_type  {};
        template <> struct imp< short, unsigned short, false, false > : true_type  {};
        template <> struct imp< short, int, false, false > : true_type  {};
        template <> struct imp< short, unsigned int, false, false > : true_type  {};
        template <> struct imp< short, long, false, false > : true_type  {};
        template <> struct imp< short, unsigned long, false, false > : true_type  {};

        template <> struct imp< short, char const&, false, false > : true_type  {};
        template <> struct imp< short, short const&, false, false > : true_type  {};
        template <> struct imp< short, int const&, false, false > : true_type  {};
        template <> struct imp< short, long const&, false, false > : true_type  {};
        template <> struct imp< short, unsigned char const&, false, false > : true_type  {};
        template <> struct imp< short, unsigned short const&, false, false > : true_type  {};
        template <> struct imp< short, unsigned int const&, false, false > : true_type  {};
        template <> struct imp< short, unsigned long const&, false, false > : true_type  {};

        template <> struct imp< int, char, false, false > : true_type  {};
        template <> struct imp< int, unsigned char, false, false > : true_type  {};
        template <> struct imp< int, short, false, false > : true_type  {};
        template <> struct imp< int, unsigned short, false, false > : true_type  {};
        template <> struct imp< int, int, false, false > : true_type  {};
        template <> struct imp< int, unsigned int, false, false > : true_type  {};
        template <> struct imp< int, long, false, false > : true_type  {};
        template <> struct imp< int, unsigned long, false, false > : true_type  {};

        template <> struct imp< int, char const&, false, false > : true_type  {};
        template <> struct imp< int, short const&, false, false > : true_type  {};
        template <> struct imp< int, int const&, false, false > : true_type  {};
        template <> struct imp< int, long const&, false, false > : true_type  {};
        template <> struct imp< int, unsigned char const&, false, false > : true_type  {};
        template <> struct imp< int, unsigned short const&, false, false > : true_type  {};
        template <> struct imp< int, unsigned int const&, false, false > : true_type  {};
        template <> struct imp< int, unsigned long const&, false, false > : true_type  {};

        template <> struct imp< long, char, false, false > : true_type  {};
        template <> struct imp< long, unsigned char, false, false > : true_type  {};
        template <> struct imp< long, short, false, false > : true_type  {};
        template <> struct imp< long, unsigned short, false, false > : true_type  {};
        template <> struct imp< long, int, false, false > : true_type  {};
        template <> struct imp< long, unsigned int, false, false > : true_type  {};
        template <> struct imp< long, long, false, false > : true_type  {};
        template <> struct imp< long, unsigned long, false, false > : true_type  {};

        template <> struct imp< long, char const&, false, false > : true_type  {};
        template <> struct imp< long, short const&, false, false > : true_type  {};
        template <> struct imp< long, int const&, false, false > : true_type  {};
        template <> struct imp< long, long const&, false, false > : true_type  {};
        template <> struct imp< long, unsigned char const&, false, false > : true_type  {};
        template <> struct imp< long, unsigned short const&, false, false > : true_type  {};
        template <> struct imp< long, unsigned int const&, false, false > : true_type  {};
        template <> struct imp< long, unsigned long const&, false, false > : true_type  {};
#endif

        template <typename T,typename S,bool B>
        struct imp<T, S, true, B>
            : public true_type {};

        template <typename S,typename T,bool B>
        struct imp<T, S, B, true>
            : public false_type {};

      }
    }
  }
  BOOST_TT_AUX_BOOL_TRAIT_DEF2(is_assignable,To,From,(::boost::type_traits::detail::is_assignable::imp<To,From>::type::value))
#else // BOOST_IS_ASSIGNABLE

  BOOST_TT_AUX_BOOL_TRAIT_DEF2(is_assignable,To,From,BOOST_IS_ASSIGNABLE(To,From))

#endif // BOOST_IS_ASSIGNABLE


}

#include <boost/type_traits/detail/bool_trait_undef.hpp>


#endif // doc

#endif // header

