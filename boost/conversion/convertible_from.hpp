//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////


/*!
 @file
 @brief
 Defines the free function @c mcf.
 */
#ifndef BOOST_CONVERSION_CONVERTIBLE_FROM_HPP
#define BOOST_CONVERSION_CONVERTIBLE_FROM_HPP

#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/type_traits/is_extrinsic_convertible.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
  namespace conversion {

    //! wrapper providing implicit conversion operation to @c Target.

    template <typename Source>
    class convertible_from {
      Source val_;
    public:

      //! @brief constructor from a @c Source
      //! @Throws Whatever the  @c Source copy constructor could throw.
      convertible_from(Source source) : val_(source) {}

      //! @brief Implicit conversion to @c Target.
      //! @Effects Forwards the conversion from the reference using @c conver_to.
      //! @Returns the conversion using @c conver_to
      //! @Throws Whatever extrinsic conversion from @c Source to @c Target could throw.
      //! @Remark On compilers that supports C++0x default arguments for function template parameters,
      //!   this constructor doesn't participates on overload resolution if @c Source is not extrinsic convertible to @c Target.
      template <typename Target
#if (defined(BOOST_CONVERSION_ENABLE_CND) && !defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS))
      , typename boost::enable_if< boost::is_extrinsic_convertible<Source,Target>, int >::type = 0
#endif
      >
      operator Target() const
      {
        return conversion::implicit_convert_to<Target>(val_);
      }

    };
    //! @brief makes a wrapper implicitly convertible from @c Source.
    //! The result provides implicitly conversion to any type which is extrinsic convertible from @c Source.
    //! @Returns convertible_from<Source>(s).
    //! @NoThrow.
    template <typename Source>
    convertible_from<Source> mcf(Source s)
    {
      return convertible_from<Source>(s);
    }
  }
}

#endif

