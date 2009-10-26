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

namespace boost { 
    template <typename T>
    struct type_tag {};
        
    namespace conversion {
    
    //template < typename To, typename From >
    //To convert_to(const From& val, type_tag<To> p=type_tag<To>());

  namespace partial_specialization_workaround {
    template < typename To, typename From >
    struct convert_to {
        inline static To apply(const From& val)
        {
            return To(val);
        }
    };
  }

  template < typename To, typename From >
  To convert_to(const From& val, type_tag<To>) {
    return partial_specialization_workaround::convert_to<To,From>::apply(val);
  }
  
}}

namespace boost_conversion_impl {
    template <typename Target, typename Source>
    Target convert_to_impl(Source const& from) {
        using namespace boost::conversion;
        //use boost::conversion::convert_to if ADL fails
        return convert_to<Target, Source>(from, boost::type_tag<Target>());
    }
}

namespace boost {
    template <typename Target, typename Source>
    Target convert_to(Source const& from, type_tag<Target> p=type_tag<Target>()) {
        return ::boost_conversion_impl::convert_to_impl<Target>(from);
    }
}


#endif

