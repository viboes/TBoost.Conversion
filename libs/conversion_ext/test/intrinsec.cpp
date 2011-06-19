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

#if defined(BOOST_CONVERSION_ENABLE_CND)
BOOST_STATIC_ASSERT(( ! boost::is_explicitly_convertible< X,AF_X >::value));
BOOST_STATIC_ASSERT(( ! boost::is_extrinsic_convertible< X,AF_X >::value));
#endif

//////////////////////////

void convert_to_with_implicit_constructor()
{
  {
    X x;
    ICF_X y1(x);
    ICF_X y2 = x;
  }
  {
    X x;
    ICF_X y(convert_to<ICF_X>(x));
  }
}

#define BOOST_CONVERSION_CONSTRUCT(T, VAR, EXPR) \
  T VAR(boost::conversion::explicit_convert_to<T>(EXPR))

void explicit_convert_to_with_explicit_constructor() {
  {
    X x;
    ECF_X y1(x);
    //ECF_X y2=x; // compile fails
    ECF_X y2=ECF_X(x);
  }
  {
    X x;
    //ECF_X y(convert_to<ECF_X>(x)); // compile must fail
    BOOST_CONVERSION_CONSTRUCT(ECF_X, y, x); // Maybe a macro !!!
    ECF_X y1_1(explicit_convert_to<ECF_X>(x));
#if defined(BOOST_CONVERSION_ENABLE_CND)
    ECF_X y1_2(mcf(x)); // doesn't fail as there is the constructor from X, but will fails for extrinsic conversion.
#endif
    ECF_X y2 = explicit_convert_to<ECF_X>(x);
  }

}

void convert_to_with_implicit_conversion_operator() {
  {
    ICT_X y;
    X x1(y);
    X x2=y;
  }
  {
    ICT_X y;
    X x1(convert_to<X>(y));
    X x2=convert_to<X>(y);
  }
}
void explicit_convert_to_with_explicit_conversion_operator() {
#ifndef BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
#error
  {
    ECT_X y;
    X x1(y);
    X x2=X(y);
  }
  {
    ECT_X y;
    X x1(explicit_convert_to<X>(y));
    X x2=explicit_convert_to<X>(y);
  }
#endif

}
void assign_to_with_assignemet_operator() {
  {
    X x;
    //AF_X y1(x);  // compile fails
    AF_X y2;
    y2=x;
#if defined(BOOST_CONVERSION_ENABLE_CND)
    assign_to(y2,x);
    mat(y2)=x;
#endif
  }
  {
    A a(0);
    AA aa(0);
    aa=a;
    }
#if defined(BOOST_CONVERSION_ENABLE_CND)
    {
    A a(0);
    AA aa(0);
    assign_to(aa,a);
    }
#endif
}
void mca_with_assignemet_operator() {
#if defined(BOOST_CONVERSION_ENABLE_CND)
    A a(0);
    AA aa(0);
    mca(aa) =a;
#endif
}

void assign_to_with_assignemet_operator_and_implicit_constructor() {
    {
    B b;
    AA aa(1);
    aa=b;
    }
#if defined(BOOST_CONVERSION_ENABLE_CND)
    {
    B b;
    AA aa(1);
    assign_to(aa,b);
    }
#endif
}
void mca_with_assignemet_operator_and_implicit_constructor() {
#if defined(BOOST_CONVERSION_ENABLE_CND)
    B b;
    AA aa(1);
    mca(aa)=b;
#endif
}

void assign_to_with_assignemet_operator_and_conversion_operator() {
    {
    C c;
    CC cc(1);
    cc=c;
    }
#if defined(BOOST_CONVERSION_ENABLE_CND)
    {
    C c;
    CC cc(1);
    assign_to(cc,c);
    }
#endif
}

void mca_with_assignemet_operator_and_conversion_operator() {
#if defined(BOOST_CONVERSION_ENABLE_CND)
    C c;
    CC cc(1);
    mca(cc)=c;
#endif
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
  mca_with_assignemet_operator();
  mca_with_assignemet_operator_and_implicit_constructor();
  mca_with_assignemet_operator_and_conversion_operator();

  return boost::report_errors();

}

