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
 Defines the free function @c implicitly.
 */
#ifndef BOOST_CONVERSION_CONVERTIBLE_FROM_HPP
#define BOOST_CONVERSION_CONVERTIBLE_FROM_HPP

#include <boost/conversion/config.hpp>
#if defined(BOOST_CONVERSION_IMPLICITLY_ENABLED) || defined(BOOST_CONVERSION_DOXYGEN_INVOKED)

#include <boost/conversion/implicit_convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/is_extrinsically_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/conversion/type_traits/is_copy_constructible.hpp>

namespace boost {
  namespace conversion {

    //! wrapper providing implicit conversion operation to any type extrinsicaly implicit convertible from @c Source.

    //! This wrapper is used indirectly through the @implicitly function to pass a @c Source parameter to a function waiting a parameter @c Target
    //! extrinsicaly convertible from it.
    //!
    //! Requires @c Source must be CopyConstructible

    template <typename Source, typename Enable =
#if defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
        requires(
            CopyConstructible<Source>
        )
#else
        typename enable_if_c<
            is_copy_constructible<Source>::value
          >::type
#endif
          >
    class convertible_from {
      Source val_;
    public:

      //! @brief constructor from a @c Source.
      //! @Throws Whatever the  @c Source copy constructor could throw.
      convertible_from(Source source) : val_(source) {}

      //! @brief Implicit conversion to a @c Target extrinsicaly convertible from @c Source.
      //! @Effects Forwards the conversion from the reference using @c conver_to.
      //! @Returns the conversion using @c conver_to
      //! @Throws Whatever extrinsic conversion from @c Source to @c Target could throw.
      //! @Remark On compilers that supports C++0x default arguments for function template parameters,
      //!   this conversion operator doesn't participates on overload resolution if @c Source is not extrinsic convertible to @c Target.
      template <typename Target
      , typename boost::enable_if< is_extrinsically_convertible<Source,Target>, int >::type = 0
      >
      operator Target() const
      {
        return implicit_convert_to<Target>(val_);
      }

    };

    //! @brief makes a wrapper implicitly convertible to types extrinsicly implicit convertibles from @c Source.
    //!
    //! The result provides implicitly conversion to any type which is extrinsically implicit convertible from @c Source.
    //! @Returns convertible_from<Source>(s).
    //! @NoThrow.
    //! @Example
    //! @code
    //! template <typename T>
    //! struct test {
    //!   static void fct()
    //!   {
    //!     T v;
    //!     std::cout << f(implicitly(v)) << " called" << std::endl;
    //!   }
    //! };
    //! @endcode

    template <typename Source>
    typename enable_if_c<
      is_copy_constructible<Source>::value
    , convertible_from<Source>
    >::type
    implicitly(Source s)
    {
      return convertible_from<Source>(s);
    }
  }
}
#endif

#endif

