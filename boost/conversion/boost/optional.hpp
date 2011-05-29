//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

/*!
 \file
 \brief
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

namespace boost {

  #ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING && ! defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace conversion { 
    namespace overload_workaround {
      template < class Target, class Source>
      struct convert_to< optional<Target>, optional<Source> >
      {
        inline static optional<Target> apply(optional<Source> const & from)
        {
          return (from?optional<Target>(boost::conversion::convert_to<Target>(from.get())):optional<Target>());
        }
      };
      
      template < class Target, class Source>
      struct convert_to< optional<Target>, Source > 
      {
        inline static optional<Target> apply(Source const & from)
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
      
      template < class Target, class Source>
      struct assign_to< optional<Target>, optional<Source> >
      {
        inline static optional<Target>& apply(optional<Target>& to, const optional<Source>& from)
        {
          to = from?optional<Target>(boost::conversion::convert_to<Target>(from.get())):optional<Target>();
          return to;
        }
      };
      
    }
  }
#else

  //! @brief @c convert_to overloading for source and target been @c boost::optional.
  //!
  //! @Returns If the optional source is initialized @c boost::optional<Target> initialized to the conversion of the optional value.
  //! Uninitialized  @c boost::optional<Target otherwise.
  template < class Target, class Source>
  inline optional<Target> convert_to(optional<Source> const & from
                                     , conversion::dummy::type_tag<optional<Target> > const&)
  {
    return (from?optional<Target>(boost::conversion::convert_to<Target>(from.get())):optional<Target>());
  }
  
  //! @brief @c convert_to overloading to try to convert the source to the target.
  //!
  //! We can see this specialization as a try_convert_to function.
  //! @Returns If the source is convertible to the target @c boost::optional<Target> initialized to the result of the conversion.
  //! Uninitialized  @c boost::optional<Target otherwise.
  template < class Target, class Source>
  inline optional<Target> convert_to(Source const & from
                                     , conversion::dummy::type_tag<optional<Target> > const&)
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

  //! @brief @c assign_to overloading for source and target been @c boost::optional.
  //!
  //! @Effects As if <c>to = boost::conversion::convert_to<optional<Target> >(from)</c>.
  //! @Returns The @c to parameter reference.
  template < class Target, class Source>
  inline optional<Target>& assign_to(optional<Target>& to, const optional<Source>& from
                                     , conversion::dummy::type_tag<optional<Target> > const&
                                     )
  {
    to = boost::conversion::convert_to<optional<Target> >(from);
    //to = from?optional<Target>(boost::conversion::convert_to<Target>(from.get())):optional<Target>();
    return to;
  }
#endif
}

#endif

//]
