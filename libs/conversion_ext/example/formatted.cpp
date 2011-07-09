//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[FORMATTED_CPP

#include <boost/conversion/std/string.hpp>
#include <boost/conversion/convert_to_or_fallback.hpp>
#include <string>
#include <iomanip>
#include <boost/assert.hpp>

class extract_t { };
const extract_t extract={};


template <typename T>
class extractor_stream {
  std::stringstream ios_;
  T value_;
  
public:
  
  template<typename U>
  extractor_stream& operator<< (U u) { return (ios_ << u, *this); }
  
  template<typename U>
  extractor_stream& operator>> (U u) { return (ios_ >> u, *this); }
  
  
  T operator>> (extract_t const&) {
    T value;
    ios_ >> value;
    return value;
  }
  
};

template <typename T>
class extract_to { };

class via_stream {
  std::stringstream ios_;
  
public:
  
  template<typename U>
  via_stream& operator<< (U u) { return (ios_ << u, *this); }
  
  template<typename U>
  via_stream& operator>> (U u) { return (ios_ >> u, *this); }
  
  
  template<typename T>
  T operator>> (extract_to<T> const&) {
    T value;
    ios_ >> value;
    return value;
  }
  
};



int main()
{
  {
    using namespace boost::conversion;
    {    
      std::string    hex_str = "0xFF"; // 255 in decimal
      // This call fails
      int   bad = convert_to_or_fallback<int>(hex_str, -1);
      BOOST_ASSERT(bad == -1); // Failed decimal conversion from "FF"
    }
    {
      
      std::string    hex_str = "FF"; // 255 in decimal
      
      // This call also fails
      int   bad = convert_to_or_fallback<int>(hex_str, -1);
      BOOST_ASSERT(bad == -1); // Failed decimal conversion from "FF"
      
      // Apply hex formatting while converting from string
      int ii = extractor_stream<int>() << hex_str >> std::hex >> extract;
      BOOST_ASSERT(ii == 255); // Successful hex conversion from "FF"
      
      // Apply hex formatting while converting from string      
      int iii = via_stream() 
      << hex_str 
      >> std::hex >> extract_to<int>();
      
      BOOST_ASSERT(iii == 255); // Successful hex conversion from "FF"
      
      std::string si1 = via_stream() 
      << std::uppercase << std::hex << ii  
      >> extract_to<std::string>();
      
      BOOST_ASSERT(si1 == "FF");
      
      
      // Apply hex, uppercase, showbase formatting while converting to string
      std::string si2 = via_stream() 
      << std::showbase << std::uppercase << std::hex << ii  
      >> extract_to<std::string>();
      
      BOOST_ASSERT(si2 == "0XFF");
      
      std::string double_str = "1.2345e-02";
      double d = via_stream() << double_str 
      >> extract_to<double>();
      
      std::string sd= via_stream() 
      << std::setprecision(4) << std::scientific << d
      >> extract_to<std::string>();
      
      BOOST_ASSERT(sd == double_str);
    }
  }
  
  return 0;
}

//]
