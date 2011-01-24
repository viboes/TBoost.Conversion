//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERT_TO_PAIR_HPP
#define BOOST_CONVERT_TO_PAIR_HPP

#include <string>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/convert/convert.hpp>

namespace boost {
namespace conversion {

    // std namespace can not be overloaded
    namespace partial_specialization_workaround {

        template<typename T, typename CharT, typename Traits, typename Alloc>
        struct convert_to< std::basic_string<CharT,Traits,Alloc>, T > {
            inline static std::basic_string<CharT,Traits,Alloc> apply(T const & from)
            {
                return convert<std::basic_string<CharT,Traits,Alloc> >::from(from);
            }
        }
        template<typename T, typename CharT, typename Traits, typename Alloc>
        struct assign_to< std::basic_string<CharT,Traits,Alloc>, T > {
            inline static std::basic_string<CharT,Traits,Alloc>& apply(std::basic_string<CharT,Traits,Alloc>& to, const T& from)
            {
                to = convert<std::basic_string<CharT,Traits,Alloc> >::from(from);
                return to;
            }
        };
        template<typename T, typename CharT, typename Traits, typename Alloc>
        struct convert_to< T, std::basic_string<CharT,Traits,Alloc>> {
            inline static T apply(std::basic_string<CharT,Traits,Alloc> const & from)
            {
                return convert<T>::from(from);
            }
        };
        template<typename T, typename CharT, typename Traits, typename Alloc>
        struct assign_to< T, std::basic_string<CharT,Traits,Alloc>> {
            inline static void apply(T& to, const std::basic_string<CharT,Traits,Alloc>& from)
            {
                to = convert<T>::from(from);
                return to;
            }
        };

    }
}}

#endif

