//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/type_traits for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief Type traits specializations for <boost/optional.hpp> types.
 */

#ifndef BOOST_CONVERSION_TT_BOOST_OPTIONAL_HPP
#define BOOST_CONVERSION_TT_BOOST_OPTIONAL_HPP

#include <boost/conversion/type_traits/is_assignable.hpp>
#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/optional.hpp>

namespace boost {

#if defined(BOOST_CONVERSION_NO_IS_DEFAULT_CONSTRUCTIBLE)
    template < typename T >
    struct is_constructible< optional<T> >  : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_CONSTRUCTIBLE)
    template < typename T >
    struct is_constructible< optional<T>, optional<T> > : true_type {};
#endif
#if defined(BOOST_CONVERSION_NO_IS_ASSIGNABLE)
    template < typename T >
    struct is_assignable< optional<T>, optional<T> >  : true_type {};
    template < typename T >
    struct is_assignable< optional<T>&, optional<T> const& >  : true_type {};
#endif

}

#endif

