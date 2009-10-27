//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERSION_ASSIGN_TO__HPP
#define BOOST_CONVERSION_ASSIGN_TO__HPP

#include <cstddef> //for std::size_t
#include <boost/conversion/convert_to.hpp>
#include <boost/swap.hpp>

namespace boost {    
    namespace conversion {
        namespace partial_specialization_workaround {
            template < typename To, typename From >
            struct assign_to {
                inline static To& apply(To& to, const From& from)
                {
                    to = from;
                    return to;
                }
            };
            template < typename To, typename From, std::size_t N  >
            struct assign_to<To[N],From[N]> {
                inline static To*& apply(To(&to)[N], const From(& from)[N])
                {
                    for (std::size_t i = 0; i < N; ++i)
                    {
                        to[i] = boost::conversion::convert_to(from[i], boost::dummy::type_tag<To>());
                    }
                    return to;
                }
            };
        }
    }

    namespace conversion_default {
        template < typename To, typename From >
        To& assign_to(To& to, const From& from) {
            return conversion::partial_specialization_workaround::assign_to<To,From>::apply(to, from);
        }
    }

    namespace conversion_impl {
        template <typename Target, typename Source>
        Target& assign_to_impl(Target& to, const Source& from) {
            using namespace boost::conversion_default;
            //use boost::conversion::assign_to if ADL fails
            return assign_to(to, from);
        }
    }

    namespace conversion {
        template <typename Target, typename Source>
        Target& assign_to(Target& to, const Source& from) {
            return conversion_impl::assign_to_impl<Target, Source>(to, from);
        }
    }
}



#endif

