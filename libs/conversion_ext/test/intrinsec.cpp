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
#include <iostream>
#include <boost/detail/lightweight_test.hpp>

using namespace boost;

struct B{};
struct A {
    A(int){}
    A(const B&){}
};
struct AE {
    explicit AE(const B&){}
};
struct AA {
    AA(int){}
    AA& operator=(const A&) { return *this;}
};

struct C {
    operator B()  const{return B();}
};
struct CC {
    CC(int){}
    CC& operator=(const B&) { return *this;}
};

void convert_to_with_implicit_constructor() {
    {
    B b;
    A a(b);
    }
    {
    B b;
    A a(boost::convert_to<A>(b));
    }

}
void convert_to_with_explicit_constructor() {
    {
    B b;
    AE ae(b);
    }
    {
    B b;
    AE ae(boost::convert_to<AE>(b));
    }

}

void convert_to_with_conversion_operator() {
    {
    C c;
    A a(c);
    }
    {
    C c;
    A a(boost::convert_to<A>(c));
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
    boost::assign_to(aa,a);
    }
}
void mca_with_assignemet_operator() {
    A a(0);
    AA aa(0);
    boost::mca(aa) =a;
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
    boost::assign_to(aa,b);
    }
}
void mca_with_assignemet_operator_and_implicit_constructor() {
    B b;
    AA aa(1);
    boost::mca(aa)=b;
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
    boost::assign_to(cc,c);
    }
}

void mca_with_assignemet_operator_and_conversion_operator() {
    C c;
    CC cc(1);
    boost::mca(cc)=c;
}


int main( )
{
  convert_to_with_implicit_constructor();
  convert_to_with_explicit_constructor();
  convert_to_with_conversion_operator();
  assign_to_with_assignemet_operator();
  assign_to_with_assignemet_operator_and_implicit_constructor();
  assign_to_with_assignemet_operator_and_conversion_operator();
  mca_with_assignemet_operator();
  mca_with_assignemet_operator_and_implicit_constructor();
  mca_with_assignemet_operator_and_conversion_operator();

  return boost::report_errors();

}

