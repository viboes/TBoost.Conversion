//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[OVERLOAD_CPP

#include <boost/conversion/include.hpp>
//#include <boost/conversion/std/string.hpp>
#include <string>
#include <iostream>
#include <boost/assert.hpp>


#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE) || defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE) || defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
#define BOOST_CONVERSION_DCL_DEFAULTS(X)                              \
namespace boost                                                       \
{                                                                     \
  template <> struct is_constructible< X >  : true_type {};           \
  template <> struct is_constructible< X, X const& >  : true_type {}; \
  template <> struct is_assignable< X&, X const& >  : true_type {};   \
  template <> struct is_assignable< X, X >  : true_type {};   \
}
#else
#define BOOST_CONVERSION_DCL_DEFAULTS(X)
#endif

using namespace boost::conversion;


//[OVERLOAD_CPP_FCTS
int f(int) { return 1; }
int f(std::string const&) { return 2; }
//]

//[OVERLOAD_CPP_IMPL
template <typename T>
struct ImplTest {
  static void whichOverload()
  {
    T v;
    std::cout << f(v) << " called" << std::endl;
  }
};
//]

struct IntrCvtToInt {
  operator int() const {return 0;}
};
BOOST_CONVERSION_DCL_DEFAULTS(IntrCvtToInt)

struct IntrCvtToString {
  operator std::string() const {return "";}
};
BOOST_CONVERSION_DCL_DEFAULTS(IntrCvtToString)

struct IntrCvtINtAndString {
  operator int() const {return 0;}
  operator std::string() const {return "";}
};
BOOST_CONVERSION_DCL_DEFAULTS(IntrCvtINtAndString)

struct ExtrCvtToInt {};
BOOST_CONVERSION_DCL_DEFAULTS(ExtrCvtToInt)
struct ExtrCvtToString {};
BOOST_CONVERSION_DCL_DEFAULTS(ExtrCvtToString)
struct ExtrCvtINtAndString {};
BOOST_CONVERSION_DCL_DEFAULTS(ExtrCvtINtAndString)
struct ExtrExplicitCvtToInt {};
BOOST_CONVERSION_DCL_DEFAULTS(ExtrExplicitCvtToInt)

namespace boost {
  namespace conversion {
    template <>
    struct implicit_converter_cp< int, ExtrCvtToInt> : true_type {
      int operator()(ExtrCvtToInt const&)
      {
        return 0;
      }
    };
    template <>
    struct explicit_converter_cp< int, ExtrExplicitCvtToInt> : true_type {
      int operator()(ExtrExplicitCvtToInt const&)
      {
        return 0;
      }
    };
    template <>
    struct implicit_converter_cp< int, ExtrCvtINtAndString> : true_type {
      int operator()(ExtrCvtINtAndString const&)
      {
        return 0;
      }
    };
    template <>
    struct implicit_converter_cp< std::string , ExtrCvtToString > : true_type {
      std::string operator()(ExtrCvtToString const&)
      {
        return "";
      }
    };
    template <>
    struct implicit_converter_cp< std::string , ExtrCvtINtAndString > : true_type {
      std::string operator()(ExtrCvtINtAndString const&)
      {
        return "";
      }
    };
  }
}

//[OVERLOAD_CPP_IMPLICITLY_LIKE
template <typename T>
struct ImplicitlyTest {
  static void whichOverload()
  {
    T v;
    std::cout << f(implicitly(v)) << " called" << std::endl;
  }
};
//]

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_convertible< IntrCvtToInt,int >::value));
  BOOST_STATIC_ASSERT(( !boost::conversion::is_extrinsically_convertible< IntrCvtToInt,std::string >::value));
  BOOST_STATIC_ASSERT(( !boost::conversion::is_extrinsically_convertible< IntrCvtToString,int >::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_convertible< IntrCvtToString,std::string >::value));

void impl_intrinsic_test()
{
  //[OVERLOAD_CPP_IMPL_INTRINSIC
  ImplTest<IntrCvtToInt>::whichOverload();
  ImplTest<IntrCvtToString>::whichOverload();
  //ImplTest<IntrCvtINtAndString>::whichOverload(); // compile fail
  //]
}
void impl_extrinsic_test()
{
  //[OVERLOAD_CPP_IMPL_EXTRINSIC
  //ImplTest<ExtrCvtToInt>::whichOverload(); // compile fail
  //ImplTest<ExtrCvtToString>::whichOverload(); // compile fail
  //ImplTest<ExtrCvtINtAndString>::whichOverload(); // compile fail
  //]
}

void implicitly_extrinsic_test()
{
#if defined(BOOST_CONVERSION_IMPLICITLY_ENABLED)
  //[OVERLOAD_CPP_IMPLICITLY
  McfTest<IntrCvtToInt>::whichOverload();
  ImplicitlyTest<IntrCvtToString>::whichOverload();
  ImplicitlyTest<ExtrCvtToInt>::whichOverload();
  ImplicitlyTest<ExtrCvtToString>::whichOverload();
  //ImplicitlyTest<ExtrCvtINtAndString>::whichOverload(); // compile fail
  //]
#endif
  #if 0
  //[OVERLOAD_CPP_IMPLICITLY_EXPLICIT
  ImplicitlyTest<ExtrExplicitCvtToInt>::whichOverload();
  //]
  #endif
}

int main()
{

  impl_intrinsic_test();
  implicitly_extrinsic_test();

  return 0;
}

//]
