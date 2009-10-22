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



void convert_to_with_builtin_types() {
    char c=0;
    short s=1;
    int i=2;
    long l=3;
    unsigned char uc(c);
    unsigned short us(s);
    unsigned int ui(i);
    unsigned long ul(l);
    
    c=convert_to<char>(c);
    s=convert_to<short>(c);
    i=convert_to<int>(c);
    l=convert_to<long>(c);
    uc=convert_to<unsigned char>(c);
    us=convert_to<unsigned short>(c);
    ui=convert_to<unsigned int>(c);
    ul=convert_to<unsigned long>(c);

    
    c=convert_to<char>(s);
    s=convert_to<short>(s);
    i=convert_to<int>(s);
    l=convert_to<long>(s);
    uc=convert_to<unsigned char>(s);
    us=convert_to<unsigned short>(s);
    ui=convert_to<unsigned int>(s);
    ul=convert_to<unsigned long>(s);
    
    c=convert_to<char>(i);
    s=convert_to<short>(i);
    i=convert_to<int>(i);
    l=convert_to<long>(i);
    uc=convert_to<unsigned char>(i);
    us=convert_to<unsigned short>(i);
    ui=convert_to<unsigned int>(i);
    ul=convert_to<unsigned long>(i);
    
    c=convert_to<char>(l);
    s=convert_to<short>(l);
    i=convert_to<int>(l);
    l=convert_to<long>(l);
    uc=convert_to<unsigned char>(l);
    us=convert_to<unsigned short>(l);
    ui=convert_to<unsigned int>(l);
    ul=convert_to<unsigned long>(l);
}


void assign_to_with_builtin_types() {
    char c=0;
    short s=1;
    int i=2;
    long l=3;
    unsigned char uc(c);
    unsigned short us(s);
    unsigned int ui(i);
    unsigned long ul(l);
    
    assign_to(c, 0);
    assign_to(c, c);
    assign_to(c, s);
    assign_to(c, i);
    assign_to(c, l);
    assign_to(c, uc);
    assign_to(c, us);
    assign_to(c, ui);
    assign_to(c, ul);

    assign_to(s, 1);
    assign_to(s, c);
    assign_to(s, s);
    assign_to(s, i);
    assign_to(s, l);
    assign_to(s, uc);
    assign_to(s, us);
    assign_to(s, ui);
    assign_to(s, ul);

    assign_to(i, 2);
    assign_to(i, c);
    assign_to(i, s);
    assign_to(i, i);
    assign_to(i, l);
    assign_to(i, uc);
    assign_to(i, us);
    assign_to(i, ui);
    assign_to(i, ul);

    assign_to(l, 3);
    assign_to(l, c);
    assign_to(l, s);
    assign_to(l, i);
    assign_to(l, l);
    assign_to(l, uc);
    assign_to(l, us);
    assign_to(l, ui);
    assign_to(l, ul);
}

void mca_assign_to_with_builtin_types() {
    char c=0;
    short s=1;
    int i=2;
    long l=3;
    unsigned char uc(c);
    unsigned short us(s);
    unsigned int ui(i);
    unsigned long ul(l);
    
    mca(c) = c;
    mca(c) = s;
    mca(c) = i;
    mca(c) = l;
    mca(c) = uc;
    mca(c) = us;
    mca(c) = ui;
    mca(c) = ul;

    mca(s) = c;
    mca(s) = s;
    mca(s) = i;
    mca(s) = l;
    mca(s) = uc;
    mca(s) = us;
    mca(s) = ui;
    mca(s) = ul;

    mca(i) = c;
    mca(i) = s;
    mca(i) = i;
    mca(i) = l;
    mca(i) = uc;
    mca(i) = us;
    mca(i) = ui;
    mca(i) = ul;

    mca(l) = c;
    mca(l) = s;
    mca(l) = i;
    mca(l) = l;
    mca(l) = uc;
    mca(l) = us;
    mca(l) = ui;
    mca(l) = ul;
        
}

void assign_to_transitive() {
    int a=0; int b=0; int c=0;

    //assign_to(a, assign_to(b, assign_to(c,1)));
    assign_to(a, assign_to(b, c));
        
}
    
void mca_assign_to_transitive() {
    {
    int a=0; int b=0; int c=0;

    mca(a) = mca(b) = mca(b) = 1;
        
    }
}

test_suite* init_unit_test_suite(int, char*[])
{
  test_suite* test = BOOST_TEST_SUITE("builtins");
  test->add(BOOST_TEST_CASE(&convert_to_with_builtin_types));
  test->add(BOOST_TEST_CASE(&assign_to_with_builtin_types));
  test->add(BOOST_TEST_CASE(&mca_assign_to_with_builtin_types));
  test->add(BOOST_TEST_CASE(&assign_to_transitive));
  test->add(BOOST_TEST_CASE(&mca_assign_to_transitive));
  return test;
}

