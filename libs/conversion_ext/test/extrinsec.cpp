//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/conversion/explicit_convert_to.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/ca_wrapper.hpp>
#include <boost/conversion/convertible_to.hpp>
#include <boost/conversion/convertible_from.hpp>
#include <boost/conversion/assignable_to.hpp>
#include <boost/conversion/type_traits/is_extrinsic_convertible.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include <boost/static_assert.hpp>


using namespace boost;
using namespace boost::conversion;

struct A{};
struct B{
  void k(){}
};
struct C{};


#if defined(BOOST_CONVERSION_DOUBLE_CP)
  A convert_to(const B&, dummy::type_tag<A> const&) {
    return A();
  }

  A& assign_to(A& to, const B&) {
    return to;
  }

  B convert_to(const C&, dummy::type_tag<B> const&) {
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


  void f(B) {}

  void g(convertible_to<B> cb)
  {
    cb.get().k(); // need for get()
    return f(cb); // implicit conversion from cb to B applies
  }

  template <typename T>
  typename boost::enable_if<boost::is_extrinsic_convertible<T,B>, void >::type
  h(T v)
  {
    return f(convert_to<B>(v));
  }

//////////
struct X{};

struct ICF_X {
};

namespace boost {
  namespace conversion {
    template <>
    struct converter_cp< ICF_X, X > : true_type {
      ICF_X operator()(X const &)
      {
        return ICF_X();
      }
    };
  }
}

struct ECF_X {
};

namespace boost {
  namespace conversion {
    template <>
    struct explicit_converter_cp< ECF_X, X > : true_type {
      ECF_X operator()(X const &)
      {
        return ECF_X();
      }
    };
  }
}

struct ICT_X {
};

namespace boost {
  namespace conversion {
    template <>
    struct converter_cp< X, ICT_X > : true_type {
      X operator()(ICT_X const &)
      {
        return X();
      }
    };
  }
}

struct ECT_X {
};

namespace boost {
  namespace conversion {
    template <>
    struct explicit_converter_cp< X, ECT_X > : true_type {
      X operator()(ECT_X const &)
      {
        return X();
      }
    };
  }
}


struct AF_X {
};

namespace boost {
  namespace conversion {
    template <>
    struct assigner_cp< AF_X, X > : true_type {
      AF_X& operator()(AF_X &lhs, X const&)
      {
        return lhs;
      }
    };
  }
}

//////////////////////////

  void xconvert_to_with_implicit_constructor()
  {
    {
      X x;
      ICF_X y1(convert_to<ICF_X>(x));
      ICF_X y2(mcf(x));
      mat(y2) = x;
    }
  }

  #define BOOST_CONVERSION_CONSTRUCT(T, VAR, EXPR) \
    T VAR(boost::conversion::explicit_convert_to<T>(EXPR))

  void xconvert_to_with_explicit_constructor()
  {
    {
      X x;
      //ECF_X y(convert_to<ECF_X>(x)); // compile must fail
      BOOST_CONVERSION_CONSTRUCT(ECF_X, y, x); // Maybe a macro !!!
      ECF_X y1_1(explicit_convert_to<ECF_X>(x));
      //ECF_X y1_2(mcf(x)); // fail as there is no implicit conversion.
      ECF_X y2 = explicit_convert_to<ECF_X>(x);
      //mat(y2) = x; // fails as no implicit conversion
    }

  }

  void xconvert_to_with_implicit_conversion_operator()
  {
    {
      ICT_X y;
      X x1(convert_to<X>(y));
      X x2(mcf(y));
      X x3=convert_to<X>(y);
      X x4=mcf(y);
      mat(x4) = y;
    }

  }
  void xconvert_to_with_explicit_conversion_operator()
  {
    {
      ECT_X y;
      X x1(explicit_convert_to<X>(y));
      X x2=explicit_convert_to<X>(y);
    }
  }
  void xassign_to_with_assignemet_operator()
  {
    {
      X x;
      //AF_X y1(x);  // compile fails
      AF_X y2;
      //y2=x;  // compile fails
      assign_to(y2,x);
      mat(y2)=x;
    }
  }
////



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
  f(mca(c));
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
  xconvert_to_with_implicit_constructor();
  xconvert_to_with_explicit_constructor();
  xconvert_to_with_implicit_conversion_operator();
  xconvert_to_with_explicit_conversion_operator();
  xassign_to_with_assignemet_operator();
  explicit_convert_to();
  explicit_assign_to();
  explicit_chain_assign_to();
  implicit_conversion_via_mca();
  implicit_conversion_via_mcf();
  implicit_conversion_via_convertible_to();
  implicit_conversion_via_sfinae();
  return boost::report_errors();
}

