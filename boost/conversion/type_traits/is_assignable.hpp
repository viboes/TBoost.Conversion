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

#include <boost/conversion/config.hpp>
#include <utility>
#include <complex>
#include <string>
#include <boost/fusion/tuple.hpp>

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
  template < class Target, class Source>
  struct is_assignable
  {};
}
#else

#if !defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)

#include <boost/type_traits/intrinsics.hpp>
#if !defined(BOOST_IS_ASSIGNABLE)
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/utility/declval.hpp>
#if defined(BOOST_NO_DECLTYPE)
#include <boost/typeof/typeof.hpp>
#endif // defined(BOOST_NO_DECLTYPE)
#endif // !defined(BOOST_IS_ASSIGNABLE)



// should be always the last #include directive
#include <boost/type_traits/detail/bool_trait_def.hpp>

namespace boost {
#ifndef BOOST_IS_ASSIGNABLE

  namespace detail {

    namespace is_assignable {
#if 0
#ifdef BOOST_NO_SFINAE_EXPR
      typedef char yes_type;
      struct no_type { char a[2]; };

      template<std::size_t N>
      struct dummy;

      template <class Target, class Source>
      struct impl
      {
        Target t;
        template <typename X>
        static yes_type
        test(dummy<sizeof(declval<X>() = declval<Source>())>*);

        template <typename X>
        static no_type
        test(...);
        static const bool value = sizeof(test<Target>(0)) == sizeof(yes_type);

        typedef boost::integral_constant<bool,value> type;
      };
#else // BOOST_NO_SFINAE_EXPR
      template <class Target, class Source>
      struct impl : false_type {};
#endif // BOOST_NO_SFINAE_EXPR

#else // 0

      template <class Target, class Source>
#if !defined(BOOST_NO_DECLTYPE)
      decltype((declval<Target>() = declval<Source>(), true_type()))
#else
      BOOST_TYPEOF_TPL((declval<Target>() = declval<Source>(), true_type()))
#endif
      test(int);

      template <class, class>
      static false_type test(...);

    template<class T, class U>
    struct impl {
#if !defined(BOOST_NO_DECLTYPE)
    typedef decltype(test<T, U>(0)) type;
#else
    typedef BOOST_TYPEOF_TPL((test<T, U>(0))) type;
#endif
    };
#endif //0

    }
  }
  BOOST_TT_AUX_BOOL_TRAIT_DEF2(is_assignable,To,From,(::boost::detail::is_assignable::impl<To,From>::type::value))
#else

  BOOST_TT_AUX_BOOL_TRAIT_DEF2(is_assignable,To,From,BOOST_IS_ASSIGNABLE(To,From))

#endif


}

#include <boost/type_traits/detail/bool_trait_undef.hpp>
#else
#include <boost/type_traits/integral_constant.hpp>

namespace boost {

  /**
   * States if the @c Target is assignable from the @c Source.
   *
   * Condition: @c true_type if <c>declval<Target>() = declval<Source>()</c> is well-formed when treated as an
   * unevaluated operand. Access checking is performed as if in a context unrelated to T and U.
   *
   * @Requires @c Target and @c Source shall be complete types, (possibly cv-qualified) void, or arrays of unknown bound.
   */

  template < class Target, class Source>
  struct is_assignable  : false_type
  {};

  // these specialization are needed because the compiler doesn't support SFINAE on expression

  template <> struct is_assignable< bool&, bool const& > : true_type  {};
  
  template <> struct is_assignable< int&, int > : true_type  {};
  template <> struct is_assignable< int&, int& > : true_type  {};
  template <> struct is_assignable< int&, int const& > : true_type  {};
  template <> struct is_assignable< int&, double > : true_type  {};
  template <> struct is_assignable< int&, short const& > : true_type {}; 
  template <> struct is_assignable< short&, int const& > : true_type  {};
  template <> struct is_assignable< float, int > : true_type  {};
  template <> struct is_assignable< int, float > : true_type  {};
  
  template <> struct is_assignable< char, char > : true_type  {};
  template <> struct is_assignable< char, unsigned char > : true_type  {};
  template <> struct is_assignable< char, short > : true_type  {};
  template <> struct is_assignable< char, unsigned short > : true_type  {};
  template <> struct is_assignable< char, int > : true_type  {};
  template <> struct is_assignable< char, unsigned int > : true_type  {};
  template <> struct is_assignable< char, long > : true_type  {};
  template <> struct is_assignable< char, unsigned long > : true_type  {};
  
  template <> struct is_assignable< char, char const& > : true_type  {};
  template <> struct is_assignable< char, short const& > : true_type  {};
  template <> struct is_assignable< char, int const& > : true_type  {};
  template <> struct is_assignable< char, long const& > : true_type  {};
  template <> struct is_assignable< char, unsigned char const& > : true_type  {};
  template <> struct is_assignable< char, unsigned short const& > : true_type  {};
  template <> struct is_assignable< char, unsigned int const& > : true_type  {};
  template <> struct is_assignable< char, unsigned long const& > : true_type  {};
  
  template <> struct is_assignable< short, char > : true_type  {};
  template <> struct is_assignable< short, unsigned char > : true_type  {};
  template <> struct is_assignable< short, short > : true_type  {};
  template <> struct is_assignable< short, unsigned short > : true_type  {};
  template <> struct is_assignable< short, int > : true_type  {};
  template <> struct is_assignable< short, unsigned int > : true_type  {};
  template <> struct is_assignable< short, long > : true_type  {};
  template <> struct is_assignable< short, unsigned long > : true_type  {};

  template <> struct is_assignable< short, char const& > : true_type  {};
  template <> struct is_assignable< short, short const& > : true_type  {};
  template <> struct is_assignable< short, int const& > : true_type  {};
  template <> struct is_assignable< short, long const& > : true_type  {};
  template <> struct is_assignable< short, unsigned char const& > : true_type  {};
  template <> struct is_assignable< short, unsigned short const& > : true_type  {};
  template <> struct is_assignable< short, unsigned int const& > : true_type  {};
  template <> struct is_assignable< short, unsigned long const& > : true_type  {};

  template <> struct is_assignable< int, char > : true_type  {};
  template <> struct is_assignable< int, unsigned char > : true_type  {};
  template <> struct is_assignable< int, short > : true_type  {};
  template <> struct is_assignable< int, unsigned short > : true_type  {};
  template <> struct is_assignable< int, int > : true_type  {};
  template <> struct is_assignable< int, unsigned int > : true_type  {};
  template <> struct is_assignable< int, long > : true_type  {};
  template <> struct is_assignable< int, unsigned long > : true_type  {};
  
  template <> struct is_assignable< int, char const& > : true_type  {};
  template <> struct is_assignable< int, short const& > : true_type  {};
  template <> struct is_assignable< int, int const& > : true_type  {};
  template <> struct is_assignable< int, long const& > : true_type  {};
  template <> struct is_assignable< int, unsigned char const& > : true_type  {};
  template <> struct is_assignable< int, unsigned short const& > : true_type  {};
  template <> struct is_assignable< int, unsigned int const& > : true_type  {};
  template <> struct is_assignable< int, unsigned long const& > : true_type  {};
  
  template <> struct is_assignable< long, char > : true_type  {};
  template <> struct is_assignable< long, unsigned char > : true_type  {};
  template <> struct is_assignable< long, short > : true_type  {};
  template <> struct is_assignable< long, unsigned short > : true_type  {};
  template <> struct is_assignable< long, int > : true_type  {};
  template <> struct is_assignable< long, unsigned int > : true_type  {};
  template <> struct is_assignable< long, long > : true_type  {};
  template <> struct is_assignable< long, unsigned long > : true_type  {};
  
  template <> struct is_assignable< long, char const& > : true_type  {};
  template <> struct is_assignable< long, short const& > : true_type  {};
  template <> struct is_assignable< long, int const& > : true_type  {};
  template <> struct is_assignable< long, long const& > : true_type  {};
  template <> struct is_assignable< long, unsigned char const& > : true_type  {};
  template <> struct is_assignable< long, unsigned short const& > : true_type  {};
  template <> struct is_assignable< long, unsigned int const& > : true_type  {};
  template <> struct is_assignable< long, unsigned long const& > : true_type  {};
  
}

#endif

#endif

#endif

