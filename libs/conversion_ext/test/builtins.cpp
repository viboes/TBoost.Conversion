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
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assignable_to.hpp>
#include <boost/conversion/include.hpp>
#include <boost/static_assert.hpp>

#include <boost/conversion/try_convert_to.hpp>
#include <boost/conversion/try_assign_to.hpp>

#include <boost/conversion/fp/convert_to.hpp>
#include <boost/phoenix/core/argument.hpp>


void convert_to_with_builtin_types() {
    char c=0;
    short s=1;
    int i=2;
    long l=3;
    unsigned char uc(c);
    unsigned short us(s);
    unsigned int ui(i);
    unsigned long ul(l);
    (void)uc; // WARNING removal
    (void)us; // WARNING removal
    (void)ui; // WARNING removal
    (void)ul; // WARNING removal

    c=boost::conversion::convert_to<char>(c);
    s=boost::conversion::convert_to<short>(c);
    i=boost::conversion::convert_to<int>(c);
    l=boost::conversion::convert_to<long>(c);
    uc=boost::conversion::convert_to<unsigned char>(c);
    us=boost::conversion::convert_to<unsigned short>(c);
    ui=boost::conversion::convert_to<unsigned int>(c);
    ul=boost::conversion::convert_to<unsigned long>(c);


    c=boost::conversion::convert_to<char>(s);
    s=boost::conversion::convert_to<short>(s);
    i=boost::conversion::convert_to<int>(s);
    l=boost::conversion::convert_to<long>(s);
    uc=boost::conversion::convert_to<unsigned char>(s);
    us=boost::conversion::convert_to<unsigned short>(s);
    ui=boost::conversion::convert_to<unsigned int>(s);
    ul=boost::conversion::convert_to<unsigned long>(s);

    c=boost::conversion::convert_to<char>(i);
    s=boost::conversion::convert_to<short>(i);
    i=boost::conversion::convert_to<int>(i);
    l=boost::conversion::convert_to<long>(i);
    uc=boost::conversion::convert_to<unsigned char>(i);
    us=boost::conversion::convert_to<unsigned short>(i);
    ui=boost::conversion::convert_to<unsigned int>(i);
    ul=boost::conversion::convert_to<unsigned long>(i);

    c=boost::conversion::convert_to<char>(l);
    s=boost::conversion::convert_to<short>(l);
    i=boost::conversion::convert_to<int>(l);
    l=boost::conversion::convert_to<long>(l);
    uc=boost::conversion::convert_to<unsigned char>(l);
    us=boost::conversion::convert_to<unsigned short>(l);
    ui=boost::conversion::convert_to<unsigned int>(l);
    ul=boost::conversion::convert_to<unsigned long>(l);
}

void implicit_convert_to_with_builtin_types() {
    char c=0;
    short s=1;
    int i=2;
    long l=3;
    unsigned char uc(c);
    unsigned short us(s);
    unsigned int ui(i);
    unsigned long ul(l);
    (void)uc; // WARNING removal
    (void)us; // WARNING removal
    (void)ui; // WARNING removal
    (void)ul; // WARNING removal

    c=boost::conversion::implicit_convert_to<char>(c);
    s=boost::conversion::implicit_convert_to<short>(c);
    i=boost::conversion::implicit_convert_to<int>(c);
    l=boost::conversion::implicit_convert_to<long>(c);
    uc=boost::conversion::implicit_convert_to<unsigned char>(c);
    us=boost::conversion::implicit_convert_to<unsigned short>(c);
    ui=boost::conversion::implicit_convert_to<unsigned int>(c);
    ul=boost::conversion::implicit_convert_to<unsigned long>(c);


    c=boost::conversion::implicit_convert_to<char>(s);
    s=boost::conversion::implicit_convert_to<short>(s);
    i=boost::conversion::implicit_convert_to<int>(s);
    l=boost::conversion::implicit_convert_to<long>(s);
    uc=boost::conversion::implicit_convert_to<unsigned char>(s);
    us=boost::conversion::implicit_convert_to<unsigned short>(s);
    ui=boost::conversion::implicit_convert_to<unsigned int>(s);
    ul=boost::conversion::implicit_convert_to<unsigned long>(s);

    c=boost::conversion::implicit_convert_to<char>(i);
    s=boost::conversion::implicit_convert_to<short>(i);
    i=boost::conversion::implicit_convert_to<int>(i);
    l=boost::conversion::implicit_convert_to<long>(i);
    uc=boost::conversion::implicit_convert_to<unsigned char>(i);
    us=boost::conversion::implicit_convert_to<unsigned short>(i);
    ui=boost::conversion::implicit_convert_to<unsigned int>(i);
    ul=boost::conversion::implicit_convert_to<unsigned long>(i);

    c=boost::conversion::implicit_convert_to<char>(l);
    s=boost::conversion::implicit_convert_to<short>(l);
    i=boost::conversion::implicit_convert_to<int>(l);
    l=boost::conversion::implicit_convert_to<long>(l);
    uc=boost::conversion::implicit_convert_to<unsigned char>(l);
    us=boost::conversion::implicit_convert_to<unsigned short>(l);
    ui=boost::conversion::implicit_convert_to<unsigned int>(l);
    ul=boost::conversion::implicit_convert_to<unsigned long>(l);
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

    boost::conversion::assign_to(c, 0);
    boost::conversion::assign_to(c, c);
    boost::conversion::assign_to(c, s);
    boost::conversion::assign_to(c, i);
    boost::conversion::assign_to(c, l);
    boost::conversion::assign_to(c, uc);
    boost::conversion::assign_to(c, us);
    boost::conversion::assign_to(c, ui);
    boost::conversion::assign_to(c, ul);

    boost::conversion::assign_to(s, 1);
    boost::conversion::assign_to(s, c);
    boost::conversion::assign_to(s, s);
    boost::conversion::assign_to(s, i);
    boost::conversion::assign_to(s, l);
    boost::conversion::assign_to(s, uc);
    boost::conversion::assign_to(s, us);
    boost::conversion::assign_to(s, ui);
    boost::conversion::assign_to(s, ul);

    boost::conversion::assign_to(i, 2);
    boost::conversion::assign_to(i, c);
    boost::conversion::assign_to(i, s);
    boost::conversion::assign_to(i, i);
    boost::conversion::assign_to(i, l);
    boost::conversion::assign_to(i, uc);
    boost::conversion::assign_to(i, us);
    boost::conversion::assign_to(i, ui);
    boost::conversion::assign_to(i, ul);

    boost::conversion::assign_to(l, 3);
    boost::conversion::assign_to(l, c);
    boost::conversion::assign_to(l, s);
    boost::conversion::assign_to(l, i);
    boost::conversion::assign_to(l, l);
    boost::conversion::assign_to(l, uc);
    boost::conversion::assign_to(l, us);
    boost::conversion::assign_to(l, ui);
    boost::conversion::assign_to(l, ul);
}

void lvalue_assign_to_with_builtin_types() {
    char c=0;
    short s=1;
    int i=2;
    long l=3;
    unsigned char uc(c);
    unsigned short us(s);
    unsigned int ui(i);
    unsigned long ul(l);

    boost::conversion::lvalue(c) = c;
    boost::conversion::lvalue(c) = s;
    boost::conversion::lvalue(c) = i;
    boost::conversion::lvalue(c) = l;
    boost::conversion::lvalue(c) = uc;
    boost::conversion::lvalue(c) = us;
    boost::conversion::lvalue(c) = ui;
    boost::conversion::lvalue(c) = ul;

    boost::conversion::lvalue(s) = c;
    boost::conversion::lvalue(s) = s;
    boost::conversion::lvalue(s) = i;
    boost::conversion::lvalue(s) = l;
    boost::conversion::lvalue(s) = uc;
    boost::conversion::lvalue(s) = us;
    boost::conversion::lvalue(s) = ui;
    boost::conversion::lvalue(s) = ul;

    boost::conversion::lvalue(i) = c;
    boost::conversion::lvalue(i) = s;
    boost::conversion::lvalue(i) = i;
    boost::conversion::lvalue(i) = l;
    boost::conversion::lvalue(i) = uc;
    boost::conversion::lvalue(i) = us;
    boost::conversion::lvalue(i) = ui;
    boost::conversion::lvalue(i) = ul;

    boost::conversion::lvalue(l) = c;
    boost::conversion::lvalue(l) = s;
    boost::conversion::lvalue(l) = i;
    boost::conversion::lvalue(l) = l;
    boost::conversion::lvalue(l) = uc;
    boost::conversion::lvalue(l) = us;
    boost::conversion::lvalue(l) = ui;
    boost::conversion::lvalue(l) = ul;
}

void assign_to_transitive() {
    int a=0; int b=0; //int c=0;

    //assign_to(a, assign_to(b, assign_to(c,1)));
    boost::conversion::assign_to(a, boost::conversion::assign_to(b, 1));

}

void lvalue_assign_to_transitive() {
    {
    int a=0; int b=0; int c=0;

    boost::conversion::lvalue(a) = boost::conversion::lvalue(b) = boost::conversion::lvalue(c) = 1;

    }
}

template <typename T, typename Enable = void>
struct is_lazy
    : boost::mpl::false_
{};

template <typename T, typename Enabled=void>
struct enable_functor : boost::mpl::false_ {};

template <typename T>
struct is_lazy<T, typename boost::enable_if<boost::phoenix::is_actor<T> >::type >
    : boost::mpl::true_
{};
template <typename T>
struct enable_functor<T, typename boost::enable_if<boost::phoenix::is_actor<T> >::type>  : boost::mpl::true_ {};

template <typename T>
void assert_enable_functor(T const&) {
  BOOST_STATIC_ASSERT(is_lazy<T>::type::value==true);
  BOOST_STATIC_ASSERT(enable_functor<T>::type::value==true);
  BOOST_STATIC_ASSERT(boost::conversion::enable_functor<T>::type::value==true);
}

template <typename T>
void assert_not_enable_functor(T const&) {
  //BOOST_STATIC_ASSERT(boost::conversion::enable_functor<T>::type::value==false);
  BOOST_STATIC_ASSERT(is_lazy<T>::type::value==false);
}

void fp_convert_to() {
  {
    //char c=0;
    short s=1;
    int i=2;
    long l=3;

    using boost::phoenix::placeholders::_1;

    //s=boost::conversion::fp::convert_to<short>(_1)(l) ;
    assert_not_enable_functor(i);
    assert_enable_functor(_1);
    s=boost::conversion::convert_to<short>(_1)(l) ;
    BOOST_TEST(s==3);

  }
}


int main( )
{
  convert_to_with_builtin_types();
  implicit_convert_to_with_builtin_types();
  assign_to_with_builtin_types();
  lvalue_assign_to_with_builtin_types();
  assign_to_transitive();
  lvalue_assign_to_transitive();
  fp_convert_to();
  return boost::report_errors();
}

