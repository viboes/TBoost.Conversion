//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/conversion/is_extrinsically_explicit_convertible.hpp>

struct A
{
    explicit A(int);
    A(double);
    A(int, double);
    A(A const&);
};

typedef void Function();
typedef char Array[1];

class NonCopyable {
  NonCopyable(NonCopyable&);
};

#if defined(BOOST_CONVERSION_NO_IS_EXTRINSIC_EXPLICIT_CONVERTIBLE)
namespace boost
{
  namespace conversion {

  template <> struct is_extrinsically_explicit_convertible< int, A >  : true_type {};
  template <> struct is_extrinsically_explicit_convertible< double, A >  : true_type {};
  //template <> struct is_constructible< A, int, double >  : true_type {};
  //template <> struct is_constructible< A, A const& >  : true_type {};
}
}
#endif

int main()
{
  {
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<const int, int>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<int, A>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<double, A>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void,A>::value));
  }
  {

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<void, void>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const void, void>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<void, const void>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const void, const void>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, Function>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, Function>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, const char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, const char>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<void, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const void, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, const void>::value));

  //BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, Function>::value));

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function, Function&>::value));

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function, Function*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function, Function* const>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, const Array>::value));


    BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_convertible<Function, Array&>::value));
    BOOST_STATIC_ASSERT((!boost::is_explicitly_convertible<Function, Array&>::value));
    BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, const char>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, const void>::value));

  //BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, Function>::value));

    //BOOST_STATIC_ASSERT(( boost::is_explicitly_convertible<Function&, Function&>::value));
    BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_convertible<Function&, Function&>::value));
    // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function&, Function&>::value));

  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function&, Function*>::value));
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function&, Function* const>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, const char>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function&, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, const void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, const void>::value));

  //BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, Function>::value));
  //BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, Function>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, Function&>::value));

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function*, Function*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function*, Function* const>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function*const, Function*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Function*const, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, const char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, const char>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Function*const, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, const void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, const void>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, Function>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, Function>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, const Array>::value));

  //BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, Array&>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Array, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, Array&>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const Array, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, const char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, const char>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, const char&>::value));

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Array, char*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Array, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array, char*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const Array, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, const void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, const void>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, Function>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, Function>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, Function*const >::value));

#if ! defined _MSC_VER
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, const Array>::value));
#endif
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Array&, Array&>::value));
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Array&, const Array&>::value));
  // BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, Array&>::value));
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const Array&, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, const char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, const char>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<Array&, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, const char&>::value));

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Array&, char*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<Array&, const char*>::value));
  //BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const Array&, char*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const Array&, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, const void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, const void>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, Function>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, Function>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, const Array&>::value));

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char, char>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char, const char>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const char, char>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const char, const char>::value));

  //BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, char&>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char, const char&>::value));
  //BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, char&>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const char, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, const void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, const void>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, Function>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, Function>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, const Array&>::value));

  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char&, char>::value));
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char&, const char>::value));
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const char&, char>::value));
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const char&, const char>::value));

  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char&, char&>::value));
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char&, const char&>::value));
  // BUG BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, char&>::value));
  // BUG BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const char&, const char&>::value));

  // BUG BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, char*>::value));
  // BUG BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char&, const char*>::value));
  // BUG BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, char*>::value));
  // BUG BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char&, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, const void>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, const void>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, Function>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, Function>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, Array>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, const char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, char>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, const char>::value));

  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<char*, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, char&>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, const char&>::value));

  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char*, char*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<char*, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const char*, char*>::value));
  BOOST_STATIC_ASSERT(( boost::conversion::is_extrinsically_explicit_convertible<const char*, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<NonCopyable&, NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<NonCopyable&, const NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<NonCopyable&, const volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<NonCopyable&, volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<const NonCopyable&, const NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<const NonCopyable&, const volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<volatile NonCopyable&, const volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::conversion::is_extrinsically_explicit_convertible<const volatile NonCopyable&, const volatile NonCopyable&>::value));
  // BUG BOOST_STATIC_ASSERT((!boost::conversion::is_extrinsically_explicit_convertible<const NonCopyable&, NonCopyable&>::value));
  }
}
