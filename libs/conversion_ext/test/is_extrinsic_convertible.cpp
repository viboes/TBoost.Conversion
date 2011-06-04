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
#include <boost/conversion/type_traits/is_extrinsic_convertible.hpp>
#include <boost/type_traits/is_convertible.hpp>


typedef void Function();
typedef char Array[1];

class NonCopyable {
  NonCopyable(NonCopyable&);
};


int main()
{

  {
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<void, void>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const void, void>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<void, const void>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const void, const void>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, Function>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, Function>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, const char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, const char>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<void, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const void, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, const void>::value));

  //BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, Function>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function, Function&>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function, Function*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function, Function* const>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, const char>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, const void>::value));

  //BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, Function>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function&, Function&>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function&, Function*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function&, Function* const>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, const char>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function&, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, const void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, const void>::value));

  //BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, Function>::value));
  //BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, Function>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, Function&>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function*, Function*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function*, Function* const>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function*const, Function*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Function*const, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, const char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, const char>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Function*const, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, const void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, const void>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, Function>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, Function>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, const Array>::value));

  //BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, Array&>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Array, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, Array&>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const Array, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, const char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, const char>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, const char&>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Array, char*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Array, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array, char*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const Array, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, const void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, const void>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, Function>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, Function>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, const Array>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Array&, Array&>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Array&, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, Array&>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const Array&, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, const char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, const char>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<Array&, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, const char&>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Array&, char*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<Array&, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const Array&, char*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const Array&, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, const void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, const void>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, Function>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, Function>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, const Array&>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char, char>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char, const char>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const char, char>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const char, const char>::value));

  //BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, char&>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, char&>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const char, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, const void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, const void>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, Function>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, Function>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, const Array&>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char&, char>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char&, const char>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const char&, char>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const char&, const char>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char&, char&>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char&, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, char&>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const char&, const char&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char&, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char&, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, const void>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, const void>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, Function>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, Function>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, Function&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, Function&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, Function* const>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, Function*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, Function*const >::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, const Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, Array>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, const Array>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, const Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, Array&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, const Array&>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, const char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, char>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, const char>::value));

  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<char*, const char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, char&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, const char&>::value));

  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char*, char*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<char*, const char*>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const char*, char*>::value));
  BOOST_STATIC_ASSERT(( boost::is_extrinsic_convertible<const char*, const char*>::value));
  }
  {
  BOOST_STATIC_ASSERT((boost::is_extrinsic_convertible<NonCopyable&, NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::is_extrinsic_convertible<NonCopyable&, const NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::is_extrinsic_convertible<NonCopyable&, const volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::is_extrinsic_convertible<NonCopyable&, volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::is_extrinsic_convertible<const NonCopyable&, const NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::is_extrinsic_convertible<const NonCopyable&, const volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::is_extrinsic_convertible<volatile NonCopyable&, const volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((boost::is_extrinsic_convertible<const volatile NonCopyable&, const volatile NonCopyable&>::value));
  BOOST_STATIC_ASSERT((!boost::is_extrinsic_convertible<const NonCopyable&, NonCopyable&>::value));
  }
}
