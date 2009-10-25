//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO__HPP
#define BOOST_CONVERT_TO__HPP

#include <cstddef> //for std::size_t

namespace boost { namespace conversion {
    
    template < typename To, typename From >
    To convert_to(const From& val);

  namespace partial_specialization_workaround {
    template < typename To, typename From >
    struct convert_to {
        inline static To apply(const From& val)
        {
            return To(val);
        }
    };
#if 0    
    template < typename To, typename From, std::size_t N >
    struct convert_to<To[N],From[N]> {
      inline static To[N] apply(const From (& val)[N])
      {
        To[N] to;
        for (std::size_t i = 0; i < N; ++i)
        {
          to[i] = boost::convert(from[i]);
        }
        return to;
      }
    };
#endif    
  }

  template < typename To, typename From >
  To convert_to(const From& val) {
    return partial_specialization_workaround::convert_to<To,From>::apply(val);
  }
}}

namespace boost_conversion_impl {
    template <typename Target, typename Source>
    Target convert_to_impl(Source const& from) {
        using namespace boost::conversion;
        //use boost::conversion::convert_to if ADL fails
        return convert_to<Target>(from);
    }
}

namespace boost {
    template <typename Target, typename Source>
    Target convert_to(Source const& from) {
        return ::boost_conversion_impl::convert_to_impl<Target>(from);
    }
}


#endif

