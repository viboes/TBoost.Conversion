//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/*!
 @file
 @brief
 Include this file when using conversions from @c std::istream.
 */


#ifndef BOOST_CONVERSION_EXTRACTOR_HPP
#define BOOST_CONVERSION_EXTRACTOR_HPP

#include <boost/conversion/convert_to.hpp>
#include <sstream>

namespace boost {
  namespace conversion {

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
    


    

  }
}

#endif

