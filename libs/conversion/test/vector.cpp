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
#include <boost/conversion/std/vector.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "helper.hpp"

using namespace boost;
using namespace boost::unit_test;

void explicit_convert_to() {
    std::vector<B1> vb1;
    std::vector<A1> va1(boost::convert_to<std::vector<A1> >(vb1));

    B1 b10, b11, b12, b13;
    std::vector<B1> vb2;
    vb2[0]=b10;
    vb2[1]=b11;
    vb2[2]=b12;
    vb2[3]=b13;
    std::vector<A1> va2(boost::convert_to<std::vector<A1> >(vb2));
    
    //~ std::allocator<A1> all;
    //~ std::vector<A1,std::allocator<A1> > va3(
        //~ boost::convert_to<std::vector<A1,std::allocator<A1> > >(
            //~ std::pair<
                //~ boost::reference_wrapper<std::vector<B1> const>, 
                //~ boost::reference_wrapper<std::allocator<A1> const>
            //~ >(boost::cref(vb2), boost::cref(all))));
     
    //~ boost::conversion::result_of_pack<std::vector<B1> const, std::allocator<A1> const>::type v = 
        //~ boost::conversion::pack(vb2, all);
        
    //~ std::vector<A1,std::allocator<A1> > va4(
        //~ boost::convert_to<std::vector<A1,std::allocator<A1> > >(v));
        
    //~ std::vector<A1,std::allocator<A1> > va5(
        //~ boost::convert_to<std::vector<A1,std::allocator<A1> > >(
            //~ boost::conversion::pack(vb2, all)));
        
    std::vector<A1,std::allocator<A1> > va6(
        boost::convert_to<std::vector<A1,std::allocator<A1> > >(
            boost::conversion::pack(vb2, std::allocator<A1>())));


}
void explicit_assign_to() {
    std::vector<B1> vb1;
    std::vector<A1> va1;
    boost::assign_to(va1,vb1);

    B1 b10, b11, b12, b13;
    std::vector<B1> vb2;
    vb2[0]=b10;
    vb2[1]=b11;
    vb2[2]=b12;
    vb2[3]=b13;

    boost::assign_to(va1,vb2);

}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("tuple");
  test->add(BOOST_TEST_CASE(&explicit_convert_to));
  test->add(BOOST_TEST_CASE(&explicit_assign_to));
  return test;
}

