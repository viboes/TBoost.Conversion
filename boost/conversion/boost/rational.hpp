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
 \file
 \brief
 Include this file when using conversions between @c boost::rational<> of convertible types.
 */

#ifndef BOOST_CONVERSION_PAIR__HPP
#define BOOST_CONVERSION_PAIR__HPP

#include <boost/rational.hpp>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace conversion {
      namespace detail {
        template <typename T>
        struct is_rational : mpl::false_ {};
        template <typename T>
        struct is_rational< ::boost::rational<T> > : mpl::true_ {};

      }
    }
#endif

  namespace conversion {
    namespace overload_workaround {
      //! @brief @c convert_to specialization for source and target been @c boost::rational.
      //!
      template < class T, class U>
      struct convert_to< rational<T>, rational<U> > {
        //! @Returns the target rational having as numerator and denominator the conversion from the numerator and denominator of the source rational.
        inline static rational<T> apply(rational<U> const & from)
        {
          return rational<T>(boost::conversion::convert_to<T>(from.numerator()), boost::conversion::convert_to<T>(from.denominator()));
        }
      };
      template < class T, class U>
      struct assign_to< rational<T>, rational<U> > {
        inline static rational<T>& apply(rational<T>& to, const rational<U>& from)
        {
          to.assign(boost::conversion::convert_to<T>(from.numerator()), boost::conversion::convert_to<T>(from.denominator()));
          return to;
        }
      };

    }
  }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    template < class T, class U>
    inline rational<T>& assign_to(rational<T>& to, const rational<U>& from)
    {
      return conversion::overload_workaround::assign_to<rational<T>, rational<U> >::apply(to, from);
    }
#endif

}

#endif

