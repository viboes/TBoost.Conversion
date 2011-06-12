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
#include <boost/conversion/ca_wrapper.hpp>
#include <boost/conversion/convertible_to.hpp>
#include <boost/conversion/convertible_from.hpp>
#include <boost/conversion/assignable_to.hpp>
#include <boost/conversion/type_traits/is_extrinsic_convertible.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include <boost/static_assert.hpp>


using namespace boost;

struct A{};
struct B{
  void k(){}
};
struct C{};

void f(B) {}

void g(boost::conversion::convertible_to<B> cb)
{
  cb.get().k();
  return f(cb);
}




#if defined(BOOST_CONVERSION_DOUBLE_CP)
  A convert_to(const B&, boost::conversion::dummy::type_tag<A> const&) {
    return A();
  }

  A& assign_to(A& to, const B&) {
    return to;
  }

  B convert_to(const C&, boost::conversion::dummy::type_tag<B> const&) {
    return B();
  }

  B& assign_to(B& to, const C&) {
    return to;
  }
#else
  namespace boost {
      namespace conversion {
          template <>
          struct converter< A,B > : true_type {
              A operator()(B const &)
              {
                  return A();
              }
          };
          template <>
          struct converter< B,C > : true_type {
              B operator()(C const &)
              {
                  return B();
              }
          };
      }
  }
#endif

#if defined(BOOST_CONVERSION_ENABLE_CND)
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible< B,A >::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible< C,B >::value));
#endif


  template <typename T>
  typename boost::enable_if<boost::is_extrinsic_convertible<T,B>, void >::type
  h(T v)
  {
    return f(boost::conversion::convert_to<B>(v));
  }

void explicit_convert_to() {
  using namespace boost::conversion;
    B b;
    A a(convert_to<A>(b));
    (void)a;
    C  c;
    f(convert_to<B>(c));

}

void explicit_assign_to() {
  using namespace boost::conversion;
  B b;
  A a;
  assign_to(a, b);
  mca(a)= b;
  mat(a)= b;
}

void explicit_chain_assign_to() {
  using namespace boost::conversion;
  C c;
  B b;
  A a;
  assign_to(a, assign_to(b,c));
  mca(a)= mca(b) = c;
  mat(a)= mat(b) = c;
}

void implicit_conversion_via_mca() {
  C c;
  f(boost::conversion::mca(c));
}

void implicit_conversion_via_mcf() {
  using namespace boost::conversion;
  C c;
  f(mcf(c));
  f(convertible_to<B>(c));
}

void implicit_conversion_via_convertible_to() {
  C c;
  g(c);
}

void implicit_conversion_via_sfinae() {
  C c;
  h(c);
}

int main( )
{
  explicit_convert_to();
  explicit_assign_to();
  explicit_chain_assign_to();
  implicit_conversion_via_mca();
  implicit_conversion_via_mcf();
  implicit_conversion_via_convertible_to();
  implicit_conversion_via_sfinae();
  return boost::report_errors();
}

