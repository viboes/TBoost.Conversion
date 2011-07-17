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
#include <boost/conversion/is_extrinsically_convertible.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include <boost/static_assert.hpp>


#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE) || defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE) || defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
#define BOOST_CONVERSION_DCL_DEFAULTS(X)                              \
namespace boost                                                       \
{                                                                     \
  template <> struct is_constructible< X >  : true_type {};           \
  template <> struct is_constructible< X, X const& >  : true_type {}; \
  template <> struct is_assignable< X&, X const& >  : true_type {};   \
  template <> struct is_assignable< X, X >  : true_type {};   \
}
#else
#define BOOST_CONVERSION_DCL_DEFAULTS(X)
#endif


using namespace boost;
using namespace boost::conversion;

struct A{};
BOOST_CONVERSION_DCL_DEFAULTS(A)
struct B{
  void k(){}
};
BOOST_CONVERSION_DCL_DEFAULTS(B)
struct C{};
BOOST_CONVERSION_DCL_DEFAULTS(C)


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
          struct implicit_converter_cp< A,B > : true_type {
              A operator()(B const &)
              {
                  return A();
              }
          };
          template <>
          struct implicit_converter_cp< B,C > : true_type {
              B operator()(C const &)
              {
                  return B();
              }
          };
      }
  }
#endif

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_convertible< B,A >::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_convertible< C,B >::value));


  void f(B) {}

  void g(convertible_to<B> cb)
  {
    cb.get().k(); // need for get()
    return f(cb); // implicit conversion from cb to B applies
  }

  template <typename T>
  typename boost::enable_if<boost::conversion::is_extrinsically_convertible<T,B>, void >::type
  h(T v)
  {
    return f(convert_to<B>(v));
  }

//////////
struct X{};
BOOST_CONVERSION_DCL_DEFAULTS(X)

struct ICF_X {};
BOOST_CONVERSION_DCL_DEFAULTS(ICF_X)

namespace boost {
  namespace conversion {
    template <>
    struct implicit_converter_cp< ICF_X, X > : true_type {
      ICF_X operator()(X const &)
      {
        return ICF_X();
      }
    };
  }
}

BOOST_STATIC_ASSERT(( !boost::is_convertible< X,ICF_X >::value));
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_convertible< X,ICF_X >::value));
#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible< X,ICF_X >::value));
#endif

struct ECF_X {};
BOOST_CONVERSION_DCL_DEFAULTS(ECF_X)

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
    struct implicit_converter_cp< X, ICT_X > : true_type {
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


#if defined(BOOST_CONVERSION_ENABLE_CND)
  BOOST_STATIC_ASSERT(( !boost::conversion::is_extrinsically_convertible< X,AF_X >::value));
  BOOST_STATIC_ASSERT(( !boost::conversion::is_extrinsically_explicit_convertible< X,AF_X >::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_convertible< X , ICF_X >::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible< X , ICF_X >::value));
  BOOST_STATIC_ASSERT(( boost::is_copy_assignable< ICF_X >::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_assignable< ICF_X, X >::value));

#endif

//////////////////////////

  void xconvert_to_with_implicit_constructor()
  {
    {
      X x;
      ICF_X y1(implicit_convert_to<ICF_X>(x));
      (void)y1;// remove warning: unused variable

#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)
      ICF_X y1_1(convert_to<ICF_X>(x));
      (void)y1_1;// remove warning: unused variable
#endif
#if defined(BOOST_CONVERSION_MCF_ENABLED)
      ICF_X y2(implicitly(x));
      (void)y2;// remove warning: unused variable
#endif
      assign_to(y1,x);
      lvalue(y1) = x;
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
      (void)y;// remove warning: unused variable
      ECF_X y1_1(explicit_convert_to<ECF_X>(x));
      (void)y1_1;// remove warning: unused variable
      //ECF_X y1_2(implicitly(x)); // fail as there is no implicit conversion.
      ECF_X y2 = explicit_convert_to<ECF_X>(x);
      (void)y2;// remove warning: unused variable
      //lvalue(y2) = x; // fails as no implicit conversion
    }

  }

  void xconvert_to_with_implicit_conversion_operator()
  {
    {
      ICT_X y;
      X x1(implicit_convert_to<X>(y));
      (void)x1;// remove warning: unused variable
#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)
      X x1_1(convert_to<X>(y));
      (void)x1_1;// remove warning: unused variable
#endif
#if defined(BOOST_CONVERSION_MCF_ENABLED)
      X x2(implicitly(y));
      (void)x2;// remove warning: unused variable
#endif
      X x3=implicit_convert_to<X>(y);
      (void)x3;// remove warning: unused variable
#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)
      X x3_1=convert_to<X>(y);
      (void)x3_1;// remove warning: unused variable
#endif
#if defined(BOOST_CONVERSION_MCF_ENABLED)
      X x4=implicitly(y);
      (void)x4;// remove warning: unused variable
#endif
      assign_to(x1,y);
      lvalue(x1) = y;
    }

  }
  void xconvert_to_with_explicit_conversion_operator()
  {
    {
      ECT_X y;
      X x1(explicit_convert_to<X>(y));
      (void)x1;// remove warning: unused variable
      X x2=explicit_convert_to<X>(y);
      (void)x2;// remove warning: unused variable
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
      lvalue(y2)=x;
    }
  }
////

#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)


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
  //assign_to(a, b);
  mca(a)= b;
  lvalue(a)= b;
}

void explicit_chain_assign_to() {
  using namespace boost::conversion;
  C c;
  B b;
  A a;
  assign_to(a, assign_to(b,c));
  mca(a)= mca(b) = c;
  lvalue(a)= lvalue(b) = c;
}

void implicit_conversion_via_mca() {
  C c;
  f(mca(c));
}

void implicit_conversion_via_implicitly() {
  using namespace boost::conversion;
  C c;
#if defined(BOOST_CONVERSION_MCF_ENABLED)
  f(implicitly(c));
#endif
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
#endif

int main( )
{
  xconvert_to_with_implicit_constructor();
  xconvert_to_with_explicit_constructor();
  xconvert_to_with_implicit_conversion_operator();
  xconvert_to_with_explicit_conversion_operator();
  xassign_to_with_assignemet_operator();
#if defined(BOOST_CONVERSION_ENABLE_CND) || !defined(BOOST_NO_SFINAE_EXPR)
  explicit_convert_to();
  explicit_assign_to();
  explicit_chain_assign_to();
  implicit_conversion_via_mca();
  implicit_conversion_via_implicitly();
  implicit_conversion_via_convertible_to();
  implicit_conversion_via_sfinae();
#endif
  return boost::report_errors();
}

