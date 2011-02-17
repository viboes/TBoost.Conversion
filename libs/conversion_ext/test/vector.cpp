//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/std/vector.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include "helper.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace boost;


BOOST_STATIC_ASSERT((
    boost::is_same<
        boost::conversion::result_of::pack2<std::vector<B1,std::allocator<B1> > const, std::allocator<A1> const>::type,
        std::pair<
        //~ boost::fusion::tuple<
            boost::reference_wrapper<std::vector<B1,std::allocator<B1> > const>,
            boost::reference_wrapper<std::allocator<A1> const>
        >
    >::value
    ));

void explicit_convert_to() {
    std::vector<B1> vb1;
    std::vector<A1> va1(boost::convert_to<std::vector<A1> >(vb1));
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    B1 b10, b11, b12, b13;
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    std::vector<B1> vb2;
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    vb2.reserve(5);
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    vb2[0]=b10;
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    vb2[1]=b11;
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    vb2[2]=b12;
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    vb2[3]=b13;
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;
    std::vector<A1> va2(boost::convert_to<std::vector<A1> >(vb2));
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;

    std::allocator<A1> all;
    std::vector<A1,std::allocator<A1> > va3(
        boost::convert_to<std::vector<A1,std::allocator<A1> > >(
            std::pair<
                boost::reference_wrapper<std::vector<B1> const>,
                boost::reference_wrapper<std::allocator<A1> const>
            >(boost::cref(vb2), boost::cref(all))));
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;

    std::vector<A1,std::allocator<A1> > va32(
        boost::convert_to<std::vector<A1,std::allocator<A1> > >(
            std::make_pair(boost::cref(vb2), boost::cref(all))));
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;

    boost::conversion::result_of::pack2<std::vector<B1> const, std::allocator<A1> const>::type v =
        boost::conversion::pack(vb2, all);
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;

    //~ std::vector<A1,std::allocator<A1> > va4(
        //~ boost::convert_to<std::vector<A1,std::allocator<A1> > >(v));

    //~ std::vector<A1,std::allocator<A1> > va5(
        //~ boost::convert_to<std::vector<A1,std::allocator<A1> > >(
            //~ boost::conversion::pack(vb2, all)));

    std::vector<A1,std::allocator<A1> > va6(
        boost::convert_to<std::vector<A1,std::allocator<A1> > >(
            boost::conversion::pack(vb2, std::allocator<A1>())));
    std::cout << __FILE__ << '['<<__LINE__<<"]" << std::endl;


}
void explicit_assign_to() {
    std::vector<B1> vb1;
    std::vector<A1> va1;
    boost::assign_to(va1,vb1);

    B1 b10, b11, b12, b13;
    std::vector<B1> vb2;
    vb2.reserve(5);
    vb2[0]=b10;
    vb2[1]=b11;
    vb2[2]=b12;
    vb2[3]=b13;

    boost::assign_to(va1,vb2);

}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  return boost::report_errors();
}

