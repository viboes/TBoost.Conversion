//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[OPTIONAL_HPP
#ifndef BOOST_CONVERT_TO_OPTIONAL_HPP
#define BOOST_CONVERT_TO_OPTIONAL_HPP

#include <boost/optional.hpp>
#include <boost/none.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>

namespace boost {

    #ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    namespace conversion { namespace partial_specialization_workaround {
        template < class Target, class Source>
        struct convert_to< optional<Target>, optional<Source> > {
            inline static optional<Target> apply(optional<Source> const & from)
            {
                return (from?optional<Target>(boost::convert_to<Target>(from.get())):optional<Target>());
            }
        };
        template < class Target, class Source>
        struct assign_to< optional<Target>, optional<Source> > {
            inline static optional<Target>& apply(optional<Target>& to, const optional<Source>& from)
            {
                to = from?boost::convert_to<Target>(from.get()):optional<Target>();
                return to;
            }
        };

    }}
    #else
    template < class Target, class Source>
    inline optional<Target> convert_to(optional<Source> const & from
                , boost::dummy::type_tag<optional<Target> > const&)
    {
        return (from?optional<Target>(boost::convert_to<Target>(from.get())):optional<Target>());
    }

    template < class Target, class Source>
    inline optional<Target>& assign_to(optional<Target>& to, const optional<Source>& from
                , boost::dummy::type_tag<optional<Target> > const&
                )
    {
        to = from?boost::convert_to<Target>(from.get()):optional<Target>();
        return to;
    }
    #endif
}

#endif

//]
