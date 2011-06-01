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
 Include this file when using conversions between @c boost::optional<> of convertible types.
 */

//[OPTIONAL_HPP
#ifndef BOOST_CONVERSION_OPTIONAL_HPP
#define BOOST_CONVERSION_OPTIONAL_HPP

#include <boost/optional.hpp>
#include <boost/none.hpp>
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
      struct is_optional : mpl::false_ {};
      template <typename T>
      struct is_optional< ::boost::optional<T> > : mpl::true_ {};

    }
  }
#endif

  namespace conversion { 
      /**
       * Partial specialization of @c convert_to for boost::optional
       */
      template < class Target, class Source>
      struct converter< optional<Target>, optional<Source> >
      {
        //! @Returns If the optional source is initialized @c boost::optional<Target> initialized to the conversion of the optional value.
        //! Uninitialized  @c boost::optional<Target otherwise.
        optional<Target> operator()(optional<Source> const & from)
        {
          return (from?optional<Target>(boost::conversion::convert_to<Target>(from.get())):optional<Target>());
        }
      };
      
      //! @brief @c convert_to specialization to try to convert the source to @c Target::value_type when @c Target is optional.
      //!
      //! We can see this specialization as a try_convert_to function.
      template < class Target, class Source>
      struct converter< optional<Target>, Source>
      {
        //! @Returns If the source is convertible to the target @c value_type
        //! @c Target initialized to the result of the conversion.
        //! Uninitialized  @c Target otherwise.
        optional<Target> operator()(Source const & from)
        {
          try
          {
            return optional<Target>(boost::conversion::convert_to<Target>(from));
          }
          catch (...)
          {
            return optional<Target>();
          }
        }
      };


  }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
  //! @brief @c assign_to overloading for source and target been @c boost::optional.
  //!
  //! @Effects As if <c>to = boost::conversion::convert_to<optional<Target> >(from)</c>.
  //! @Returns The @c to parameter reference.
  template < class Target, class Source>
  inline optional<Target>& assign_to(optional<Target>& to, const optional<Source>& from
  )
  {
    to = boost::conversion::convert_to<optional<Target> >(from);
    return to;
  }
#endif

}

#endif

//]
