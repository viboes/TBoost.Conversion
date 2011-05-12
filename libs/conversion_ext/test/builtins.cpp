//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include <boost/conversion/ca_wrapper.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/include.hpp>

//using namespace boost;

void convert_to_with_builtin_types() {
    char c=0;
    short s=1;
    int i=2;
    long l=3;
    unsigned char uc(c);
    unsigned short us(s);
    unsigned int ui(i);
    unsigned long ul(l);

    c=boost::convert_to<char>(c);
    s=boost::convert_to<short>(c);
    i=boost::convert_to<int>(c);
    l=boost::convert_to<long>(c);
    uc=boost::convert_to<unsigned char>(c);
    us=boost::convert_to<unsigned short>(c);
    ui=boost::convert_to<unsigned int>(c);
    ul=boost::convert_to<unsigned long>(c);


    c=boost::convert_to<char>(s);
    s=boost::convert_to<short>(s);
    i=boost::convert_to<int>(s);
    l=boost::convert_to<long>(s);
    uc=boost::convert_to<unsigned char>(s);
    us=boost::convert_to<unsigned short>(s);
    ui=boost::convert_to<unsigned int>(s);
    ul=boost::convert_to<unsigned long>(s);

    c=boost::convert_to<char>(i);
    s=boost::convert_to<short>(i);
    i=boost::convert_to<int>(i);
    l=boost::convert_to<long>(i);
    uc=boost::convert_to<unsigned char>(i);
    us=boost::convert_to<unsigned short>(i);
    ui=boost::convert_to<unsigned int>(i);
    ul=boost::convert_to<unsigned long>(i);

    c=boost::convert_to<char>(l);
    s=boost::convert_to<short>(l);
    i=boost::convert_to<int>(l);
    l=boost::convert_to<long>(l);
    uc=boost::convert_to<unsigned char>(l);
    us=boost::convert_to<unsigned short>(l);
    ui=boost::convert_to<unsigned int>(l);
    ul=boost::convert_to<unsigned long>(l);
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

    boost::assign_to(c, 0);
    boost::assign_to(c, c);
    boost::assign_to(c, s);
    boost::assign_to(c, i);
    boost::assign_to(c, l);
    boost::assign_to(c, uc);
    boost::assign_to(c, us);
    boost::assign_to(c, ui);
    boost::assign_to(c, ul);

    boost::assign_to(s, 1);
    boost::assign_to(s, c);
    boost::assign_to(s, s);
    boost::assign_to(s, i);
    boost::assign_to(s, l);
    boost::assign_to(s, uc);
    boost::assign_to(s, us);
    boost::assign_to(s, ui);
    boost::assign_to(s, ul);

    boost::assign_to(i, 2);
    boost::assign_to(i, c);
    boost::assign_to(i, s);
    boost::assign_to(i, i);
    boost::assign_to(i, l);
    boost::assign_to(i, uc);
    boost::assign_to(i, us);
    boost::assign_to(i, ui);
    boost::assign_to(i, ul);

    boost::assign_to(l, 3);
    boost::assign_to(l, c);
    boost::assign_to(l, s);
    boost::assign_to(l, i);
    boost::assign_to(l, l);
    boost::assign_to(l, uc);
    boost::assign_to(l, us);
    boost::assign_to(l, ui);
    boost::assign_to(l, ul);
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

    boost::mca(c) = c;
    boost::mca(c) = s;
    boost::mca(c) = i;
    boost::mca(c) = l;
    boost::mca(c) = uc;
    boost::mca(c) = us;
    boost::mca(c) = ui;
    boost::mca(c) = ul;

    boost::mca(s) = c;
    boost::mca(s) = s;
    boost::mca(s) = i;
    boost::mca(s) = l;
    boost::mca(s) = uc;
    boost::mca(s) = us;
    boost::mca(s) = ui;
    boost::mca(s) = ul;

    boost::mca(i) = c;
    boost::mca(i) = s;
    boost::mca(i) = i;
    boost::mca(i) = l;
    boost::mca(i) = uc;
    boost::mca(i) = us;
    boost::mca(i) = ui;
    boost::mca(i) = ul;

    boost::mca(l) = c;
    boost::mca(l) = s;
    boost::mca(l) = i;
    boost::mca(l) = l;
    boost::mca(l) = uc;
    boost::mca(l) = us;
    boost::mca(l) = ui;
    boost::mca(l) = ul;

}

void assign_to_transitive() {
    int a=0; int b=0; //int c=0;

    //assign_to(a, assign_to(b, assign_to(c,1)));
    boost::assign_to(a, boost::assign_to(b, 1));

}

void mca_assign_to_transitive() {
    {
    int a=0; int b=0; int c=0;

    boost::mca(a) = boost::mca(b) = boost::mca(c) = 1;

    }
}

int main( )
{
  convert_to_with_builtin_types();
  assign_to_with_builtin_types();
  mca_assign_to_with_builtin_types();
  assign_to_transitive();
  mca_assign_to_transitive();
  return boost::report_errors();
}

