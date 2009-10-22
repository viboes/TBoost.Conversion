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
#include <boost/conversion/ca_wrapper.hpp>
#include <iostream>
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace boost::unit_test;

struct B{};
struct A {
    A(int){};
    A(const B&b){};
};
struct AE {
    explicit AE(const B&b){};
};
struct AA {
    AA(int){};
    AA& operator=(const A&a) { return *this;}
};

struct C {
    operator B()  const{return B();};    
};
struct CC {
    CC(int){};
    CC& operator=(const B&b) { return *this;}
};

void convert_to_with_implicit_constructor() {
    {
    B b;
    A a(b);
    }
    {
    B b;
    A a(convert_to<A>(b));
    }
    
}
void convert_to_with_explicit_constructor() {
    {
    B b;
    AE ae(b);
    }
    {
    B b;
    AE ae(convert_to<AE>(b));
    }
    
}

void convert_to_with_conversion_operator() {
    {
    C c;
    A a(c);
    }
    {
    C c;
    A a(convert_to<A>(c));
    }
    
}
void assign_to_with_assignemet_operator() {
    {
    A a(0);
    AA aa(0);
    aa=a;
    }
    {
    A a(0);
    AA aa(0);
    assign_to(aa,a);
    }
}
void mca_with_assignemet_operator() {
    A a(0);
    AA aa(0);
    mca(aa) =a;  
}

void assign_to_with_assignemet_operator_and_implicit_constructor() {
    {
    B b;
    AA aa(1);
    aa=b;
    }
    {
    B b;
    AA aa(1);
    assign_to(aa,b);
    }
}    
void mca_with_assignemet_operator_and_implicit_constructor() {
    B b;
    AA aa(1);
    mca(aa)=b;    
}

void assign_to_with_assignemet_operator_and_conversion_operator() {
    {
    C c;
    CC cc(1);
    cc=c;
    }
    {
    C c;
    CC cc(1);
    assign_to(cc,c);
    }
}

void mca_with_assignemet_operator_and_conversion_operator() {
    C c;
    CC cc(1);
    mca(cc)=c;
}
    

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("intrinsec");
  test->add(BOOST_TEST_CASE(&convert_to_with_implicit_constructor));
  test->add(BOOST_TEST_CASE(&convert_to_with_explicit_constructor));
  test->add(BOOST_TEST_CASE(&convert_to_with_conversion_operator));
  test->add(BOOST_TEST_CASE(&assign_to_with_assignemet_operator));
  test->add(BOOST_TEST_CASE(&assign_to_with_assignemet_operator_and_implicit_constructor));
  test->add(BOOST_TEST_CASE(&assign_to_with_assignemet_operator_and_conversion_operator));
  test->add(BOOST_TEST_CASE(&mca_with_assignemet_operator));
  test->add(BOOST_TEST_CASE(&mca_with_assignemet_operator_and_implicit_constructor));
  test->add(BOOST_TEST_CASE(&mca_with_assignemet_operator_and_conversion_operator));
    
  return test;
    
}

