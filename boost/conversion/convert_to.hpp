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
    namespace dummy {
        template <typename T> struct base_tag {};
        template <typename T> struct type_tag : public base_tag<T> {};
    }
    namespace conversion {
        namespace partial_specialization_workaround {
            template < typename To, typename From >
            struct convert_to {
                inline static To apply(const From& val)
                {
                    return To((val));
                }
            };
        }
        
        template < typename To, typename From >
        To convert_to(const From& val, dummy::type_tag<To> const&) {
            return conversion::partial_specialization_workaround::convert_to<To,From>::apply(val);
        }
    }
    namespace conversion_impl {
            template <typename Target, typename Source>
            Target convert_to_impl(Source const& from) {
                using namespace boost::conversion;
                //use boost::conversion::convert_to if ADL fails
                return convert_to(from, boost::dummy::type_tag<Target>());
            }
    }
    template <typename Target, typename Source>
    Target convert_to(Source const& from, boost::dummy::base_tag<Target> const& p=boost::dummy::base_tag<Target>()) {
        (void)p;
        return conversion_impl::convert_to_impl<Target>(from);
    }

}

#endif

