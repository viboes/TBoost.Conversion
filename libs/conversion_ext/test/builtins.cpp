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
#include <boost/static_assert.hpp>

#include <boost/conversion/try_convert_to.hpp>

#include <boost/conversion/fp/convert_to.hpp>
#include <boost/phoenix/core/argument.hpp>

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

void mca_assign_to_with_builtin_types() {
    char c=0;
    short s=1;
    int i=2;
    long l=3;
    unsigned char uc(c);
    unsigned short us(s);
    unsigned int ui(i);
    unsigned long ul(l);

    boost::conversion::mca(c) = c;
    boost::conversion::mca(c) = s;
    boost::conversion::mca(c) = i;
    boost::conversion::mca(c) = l;
    boost::conversion::mca(c) = uc;
    boost::conversion::mca(c) = us;
    boost::conversion::mca(c) = ui;
    boost::conversion::mca(c) = ul;

    boost::conversion::mca(s) = c;
    boost::conversion::mca(s) = s;
    boost::conversion::mca(s) = i;
    boost::conversion::mca(s) = l;
    boost::conversion::mca(s) = uc;
    boost::conversion::mca(s) = us;
    boost::conversion::mca(s) = ui;
    boost::conversion::mca(s) = ul;

    boost::conversion::mca(i) = c;
    boost::conversion::mca(i) = s;
    boost::conversion::mca(i) = i;
    boost::conversion::mca(i) = l;
    boost::conversion::mca(i) = uc;
    boost::conversion::mca(i) = us;
    boost::conversion::mca(i) = ui;
    boost::conversion::mca(i) = ul;

    boost::conversion::mca(l) = c;
    boost::conversion::mca(l) = s;
    boost::conversion::mca(l) = i;
    boost::conversion::mca(l) = l;
    boost::conversion::mca(l) = uc;
    boost::conversion::mca(l) = us;
    boost::conversion::mca(l) = ui;
    boost::conversion::mca(l) = ul;

}

void assign_to_transitive() {
    int a=0; int b=0; //int c=0;

    //assign_to(a, assign_to(b, assign_to(c,1)));
    boost::conversion::assign_to(a, boost::conversion::assign_to(b, 1));

}

void mca_assign_to_transitive() {
    {
    int a=0; int b=0; int c=0;

    boost::conversion::mca(a) = boost::conversion::mca(b) = boost::conversion::mca(c) = 1;

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
  assign_to_with_builtin_types();
  mca_assign_to_with_builtin_types();
  assign_to_transitive();
  mca_assign_to_transitive();
  fp_convert_to();
  return boost::report_errors();
}

