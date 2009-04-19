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
    template < typename To, typename From >
    struct assign_to {
      inline static To& apply(const From& from, To& to)
      {
        to = from;
        return to;
      }
    };
    template < typename To, typename From, std::size_t N  >
    struct assign_to<To[N],From[N]> {
      inline static To*& apply(const From(& from)[N], To (&to)[N])
      {
        for (std::size_t i = 0; i < N; ++i)
        {
          to[i] = boost::convert_to(from[i]);
        }
        return to;
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

  template < typename To, typename From >
  To& assign_to(const From& from, To& to) {
    return partial_specialization_workaround::assign_to<To,From>::apply(from, to);
  }


}

#endif

