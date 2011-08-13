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
#include <boost/conversion/assignable_to.hpp>
#include <boost/conversion/assignable_to.hpp>
#include <boost/conversion/convertible_from.hpp>
#include <iostream>
#include <boost/detail/lightweight_test.hpp>
#include <boost/static_assert.hpp>

using namespace boost;
using namespace boost::conversion;

struct B{};
struct A {
    A(int){}
    A(const B&){}
};
struct AE {
    explicit AE(B){}
};
struct AA {
  AA(int){}
  AA(const A&){}
  AA& operator=(const A&) { return *this;}
  //AA& operator=(const B&) { return *this;}
};

struct C {
    operator B()  const{ return B(); }
};
struct CC {
  CC(int){}
  CC(const B&){}
  CC& operator=(const B&) { return *this;}
};

//////////
struct X{};

struct ICF_X {
  ICF_X(X const&) {}
};
struct ECF_X {
  explicit ECF_X(X const&) {}
};
struct ICT_X {
    operator X()  const{ return X(); }
};

#ifndef BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
struct ECT_X {
    explicit operator X() const { return X(); }
};
#endif

struct AF_X {
  AF_X& operator=(X) { return *this; }
};


#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
namespace boost
{
  template <> struct is_constructible< B >  : true_type {};
  template <> struct is_constructible< X >  : true_type {};
}
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
namespace boost
{
  template <> struct is_constructible< B, B const& >  : true_type {};
  template <> struct is_constructible< X, X const& >  : true_type {};
  template <> struct is_constructible< ICF_X, X const& >  : true_type {};
  template <> struct is_constructible< ECF_X, X const& >  : true_type {};
  template <> struct is_constructible< ECF_X, X >  : true_type {};
  template <> struct is_constructible< A, int >  : true_type {};
  template <> struct is_constructible< A, B >  : true_type {};
  template <> struct is_constructible< CC, int >  : true_type {};
  template <> struct is_constructible< AA, int >  : true_type {};
  template <> struct is_constructible< AA, A const& >  : true_type {};
  template <> struct is_constructible< CC, B const& >  : true_type {};
  template <> struct is_constructible< AE, B >  : true_type {};

}
#endif

#if defined BOOST_CONVERSION_NO_IS_EXPLICIT_CONVERTIBLE
namespace boost
{
  template <> struct is_explicitly_convertible< X, ECF_X >  : true_type {};
}
#endif

#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
namespace boost
{
  template <> struct is_assignable< X&, X const& >  : true_type {};
  template <> struct is_assignable< B&, B const& >  : true_type {};
  template <> struct is_assignable< A, B >  : true_type {};
  template <> struct is_assignable< CC, B >  : true_type {};
  template <> struct is_assignable< CC, C >  : true_type {};
  template <> struct is_assignable< AA, A >  : true_type {};
  template <> struct is_assignable< AA&, A const& >  : true_type {};
  template <> struct is_assignable< AF_X, X >  : true_type {};
  template <> struct is_assignable< AA, B >  : true_type {};
}
#endif


BOOST_STATIC_ASSERT(( ! boost::is_convertible< X,ECF_X >::value));
BOOST_STATIC_ASSERT(( boost::is_explicitly_convertible< X,ECF_X >::value));
BOOST_STATIC_ASSERT(( ! boost::conversion::is_extrinsically_convertible< X,ECF_X >::value));
BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible< X,ECF_X >::value));
BOOST_STATIC_ASSERT(( ! boost::is_explicitly_convertible< X,AF_X >::value));
BOOST_STATIC_ASSERT(( ! boost::conversion::is_extrinsically_convertible< X,AF_X >::value));

//////////////////////////

void convert_to_with_implicit_constructor()
{
  {
    X x;
    ICF_X y1(x);
    (void)y1; // WARNING removal
    ICF_X y2 = x;
    (void)y2; // WARNING removal
  }
  {
    X x;
    ICF_X y(convert_to<ICF_X>(x));
    (void)y; // WARNING removal
  }
}


void impl_cnv(ECF_X) {}

#define BOOST_CONVERSION_CONSTRUCT(T, VAR, EXPR) \
  T VAR(boost::conversion::explicit_convert_to<T>(EXPR))

void explicit_convert_to_with_explicit_constructor() {
  {
    X x;
    ECF_X y1(x);
    (void)y1; // WARNING removal

    //ECF_X y2=x; // compile fails
    //(void)y2; // WARNING removal
    //impl_cnv(x); // fail as x is not implicit convertible to ECF_X.

    ECF_X y3=ECF_X(x);
    (void)y3; // WARNING removal
  }
  {
    X x;
    BOOST_CONVERSION_CONSTRUCT(ECF_X, y, x); // Maybe a macro !!!
    ECF_X y1_1(explicit_convert_to<ECF_X>(x));
    (void)y1_1; // WARNING removal
#if defined(BOOST_CONVERSION_IMPLICITLY_ENABLED)
    //ECF_X y1_2(implicitly(x)); // should fail as ambiguous: ECF_X(X) and ECF_X(ECF_X&const). fails only with gcc4.3. 0x
#endif

#if defined(BOOST_CONVERSION_IMPLICITLY_ENABLED)
    //impl_cnv(implicitly(x)); // fail as x is not implicit convertible to ECF_X.
#endif
    ECF_X y3 = explicit_convert_to<ECF_X>(x);
    (void)y3; // WARNING removal
  }

}

void convert_to_with_implicit_conversion_operator() {
  {
    ICT_X y;
    X x1(y);
    (void)x1;// remove warning: unused variable
    X x2=y;
    (void)x2;// remove warning: unused variable
  }
  {
    ICT_X y;
    X x1(convert_to<X>(y));
    (void)x1;// remove warning: unused variable
    X x2=convert_to<X>(y);
    (void)x2;// remove warning: unused variable
  }
}
void explicit_convert_to_with_explicit_conversion_operator() {
#ifndef BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
  {
    ECT_X y;
    X x1(y);
    X x2=X(y);
    (void)x2; // WARNING removal
  }
  {
    ECT_X y;
    X x1(explicit_convert_to<X>(y));
    X x2=explicit_convert_to<X>(y);
    (void)x2; // WARNING removal
  }
#endif

}
void assign_to_with_assignemet_operator() {
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_assignable_tagged< AF_X, X >::value));
  {
    X x;
    //AF_X y1(x);  // compile fails
    AF_X y2;
    y2=x;
    assign_to(y2,x);
    lvalue(y2)=x;
  }
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
void lvalue_with_assignemet_operator() {
    A a(0);
    AA aa(0);
    lvalue(aa) =a;
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
    lvalue(aa)=b;
    assign_to(aa,b);
    }
}
void lvalue_with_assignemet_operator_and_implicit_constructor() {
    B b;
    AA aa(1);
    lvalue(aa)=b;
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
    lvalue(cc)=c;
    //assign_to(cc,c);
    }
}

void lvalue_with_assignemet_operator_and_conversion_operator() {
    C c;
    CC cc(1);
    lvalue(cc)=c;
}


int main( )
{
  convert_to_with_implicit_constructor();
  explicit_convert_to_with_explicit_constructor();
  convert_to_with_implicit_conversion_operator();
  explicit_convert_to_with_explicit_conversion_operator();
  assign_to_with_assignemet_operator();
  assign_to_with_assignemet_operator_and_implicit_constructor();
  assign_to_with_assignemet_operator_and_conversion_operator();
  lvalue_with_assignemet_operator();
  lvalue_with_assignemet_operator_and_implicit_constructor();
  lvalue_with_assignemet_operator_and_conversion_operator();

  return boost::report_errors();

}

