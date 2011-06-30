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

struct IntrCvtToString {
  operator std::string() const {return "";}
};

struct IntrCvtINtAndString {
  operator int() const {return 0;}
  operator std::string() const {return "";}
};

struct ExtrCvtToInt {};
struct ExtrCvtToString {};
struct ExtrCvtINtAndString {};
struct ExtrExplicitCvtToInt {};

namespace boost {
  namespace conversion {
    template <>
    struct converter_cp< int, ExtrCvtToInt> : true_type {
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
    struct converter_cp< int, ExtrCvtINtAndString> : true_type {
      int operator()(ExtrCvtINtAndString const&)
      {
        return 0;
      }
    };
    template <>
    struct converter_cp< std::string , ExtrCvtToString > : true_type {
      std::string operator()(ExtrCvtToString const&)
      {
        return "";
      }
    };
    template <>
    struct converter_cp< std::string , ExtrCvtINtAndString > : true_type {
      std::string operator()(ExtrCvtINtAndString const&)
      {
        return "";
      }
    };
  }
}

//[OVERLOAD_CPP_MCF_LIKE
template <typename T>
struct McfTest {
  static void whichOverload()
  {
    T v;
    std::cout << f(mcf(v)) << " called" << std::endl;
  }
};
//]

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

void mcf_extrinsic_test()
{
  //[OVERLOAD_CPP_MCF
#if defined(BOOST_CONVERSION_MCF_ENABLED)
  McfTest<IntrCvtToInt>::whichOverload();
  McfTest<IntrCvtToString>::whichOverload();
  McfTest<ExtrCvtToInt>::whichOverload();
  McfTest<ExtrCvtToString>::whichOverload();
#endif
  //McfTest<ExtrCvtINtAndString>::whichOverload(); // compile fail
  //]
  #if 0
  //[OVERLOAD_CPP_MCF_EXPLICIT
  McfTest<ExtrExplicitCvtToInt>::whichOverload();
  //]
  #endif
}

int main()
{

  impl_intrinsic_test();
  mcf_extrinsic_test();

  return 0;
}

//]
