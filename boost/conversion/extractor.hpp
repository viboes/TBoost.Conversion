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
#include <istream>

namespace boost {
  namespace conversion {

    class extract_t { };
    const extract_t extract={};

    template <typename T>
    class extractor {
      T value_;

    public:
      extractor(std::istream &is) {
        is >> value_;
      }

      T value() const {
        return value_;
      };
      //operator T() const {return value();};
    };

    template <typename T>
    class extractor_stream {
      std::stringstream ios_;
      T value_;

    public:

      template<typename U>
      extractor_stream& operator<< (U u) { return (ios_ << u, *this); }

      template<typename U>
      extractor_stream& operator>> (U u) { return (ios_ >> u, *this); }


      extractor<T> operator>> (extract_t const&) {
        return extractor<T>(ios_);
      }


      //operator T() const {return value();};
    };
    template<typename T>
    struct explicit_converter< T, extractor_stream<T>
        > : true_type
    {
      T operator()(extractor_stream<T> const & from)
      {
        //return from.value();
        return convert_to<T>(const_cast<extractor_stream<T> &>(from)>>extract);
      }
    };

    template<typename T>
    struct explicit_converter< T, extractor<T>
        > : true_type
    {
      T operator()(extractor<T> const & from)
      {
        return from.value();
      }
    };

    template <typename Target>
    Target extract2(std::istream &is) {
      return convert_to<Target>(extractor<Target>(is));
    }

  }
}

#endif

