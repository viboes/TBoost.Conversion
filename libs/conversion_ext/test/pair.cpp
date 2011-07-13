//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/std/pair.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include "helper.hpp"
#include <boost/static_assert.hpp>
#include <boost/conversion/type_traits/is_convertible.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/conversion/type_traits/is_explicitly_convertible.hpp>
#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/is_extrinsically_convertible.hpp>
#include <boost/conversion/is_extrinsically_assignable.hpp>

using namespace boost;

#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)
BOOST_STATIC_ASSERT(( !boost::is_constructible<std::pair<A1,A2>, std::pair<B1,B2> >::value));
BOOST_STATIC_ASSERT(( !boost::is_explicitly_convertible<std::pair<B1,B2>, std::pair<A1,A2> >::value));
BOOST_STATIC_ASSERT(( !boost::is_convertible<std::pair<B1,B2>, std::pair<A1,A2> >::value));
#endif

#if defined(BOOST_CONVERSION_ENABLE_CND)
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_convertible<std::pair<B1,B2>, std::pair<A1,A2> >::value));
BOOST_STATIC_ASSERT(( !boost::is_assignable<std::pair<A1,A2>, std::pair<B1,B2> >::value));
BOOST_STATIC_ASSERT(( boost::conversion::assigner<std::pair<A1,A2>, std::pair<B1,B2> >::value));
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_assignable<std::pair<A1,A2>, std::pair<B1,B2> >::value));
#endif

void explicit_convert_to() {
    B1 b1;
    B2 b2;
    std::pair<B1,B2> b;
#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)
    {
    std::pair<A1,A2> a1(boost::conversion::convert_to<std::pair<A1,A2> >(b));
    std::pair<A1,A2> a2(boost::conversion::convert_to<std::pair<A1,A2> >(std::pair<B1,B2>(b1,b2)));
    std::pair<A1,A2> a3(boost::conversion::convert_to<std::pair<A1,A2> >(std::make_pair(b1,b2)));
    }
#endif
    std::pair<A1,A2> a1(boost::conversion::implicit_convert_to<std::pair<A1,A2> >(b));
    std::pair<A1,A2> a2(boost::conversion::implicit_convert_to<std::pair<A1,A2> >(std::pair<B1,B2>(b1,b2)));
    std::pair<A1,A2> a3(boost::conversion::implicit_convert_to<std::pair<A1,A2> >(std::make_pair(b1,b2)));
}
void explicit_assign_to() {
    B1 b1;
    B2 b2;
    std::pair<A1,A2> a;
    std::pair<B1,B2> b;
    boost::conversion::assign_to(a,b);
    boost::conversion::assign_to(a, std::pair<B1,B2>(b1,b2));
    boost::conversion::assign_to(a, std::make_pair(b1,b2));

}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

