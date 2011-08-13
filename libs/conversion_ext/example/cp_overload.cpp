//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[CP_OVERLOAD_CPP

#include <boost/conversion/explicit_convert_to.hpp>
#include <boost/conversion/is_extrinsically_explicit_convertible.hpp>
#include <iostream>

namespace UNS {
  struct S{};
  int explicit_convert_to(S const&
      , boost::conversion::dummy::type_tag<int> const&) {
    return 1;
  }
}
#if defined BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE_TAGGED
namespace boost {
  namespace conversion {
    template <>
    struct is_extrinsically_explicit_convertible_tagged<UNS::S,int>
    : true_type {};
  }
}
#endif
int main()
{
  using namespace boost::conversion;
  UNS::S s;
  std::cout << explicit_convert_to<int>(s) << std::endl;

  return 0;
}

//]
