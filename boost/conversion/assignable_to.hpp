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
 Defines the free function @c mca.
 */
#ifndef BOOST_CONVERSION_ASSIGNABLE_TO_HPP
#define BOOST_CONVERSION_ASSIGNABLE_TO_HPP

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/type_traits/is_extrinsic_convertible.hpp>
#include <boost/conversion/type_traits/is_extrinsic_assignable.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
  namespace conversion {

    //! wrapper providing assignment from extrinsic assignable to @c Target.

    template <typename Target>
    class assignable_to {
    public:
      Target& ref_;

      //! default copy constructor
      //! @NoThrow.
      //assignable_to(assignable_to const& r) : ref_(r.ref_) { }

      //! constructor from a reference
      //! @NoThrow.
      assignable_to(Target& r) : ref_(r) {}

//      //! Implicit conversion to @c U.
//      //! @Effects Forwards the conversion from the reference using @c conver_to.
//      //! @Returns @c *this
//      //! @Throws Whatever @c convert_to throws.
//      template <typename U
//#if defined(BOOST_CONVERSION_ENABLE_CND) && !defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
//      , typename boost::enable_if< boost::is_extrinsic_convertible<Target,U>, int >::type = 0
//#endif
//      >
//      operator U()
//      {
//        return boost::conversion::convert_to<U>(ref_);
//      }

      //! Assignment.
      //!
      //! @Effects Forwards the assignment to the reference.
      //! @Returns @c *this
      //! @Throws Whatever @c Target assignment can throws.
      assignable_to& operator =(assignable_to<Target> const& u)
      {
        ref_ = u.ref_;
        return *this;
      }

      //! Assignment from a assignable_to wrapping a type @c Source convertible to Target.
      //!
      //! @Effects Forwards the assignment to the reference using @c assign_to.
      //! @Returns @c *this
      //! @Throws Whatever @c assign_to throws.
      //! @Remark This constructor doesn't participates on overload resolution if @c Source is not extrinsic assignable to @c Target.
      template <typename Source>
#if defined(BOOST_CONVERSION_ENABLE_CND) && !defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
      typename boost::enable_if< boost::is_extrinsic_assignable<Target,Source>, assignable_to& >::type
#else
      assignable_to&
#endif
      operator =(assignable_to<Source> const& s)
      {
        boost::conversion::assign_to(ref_, s.ref_);
        return *this;
      }

      //! Assignment from a type @c Source assignable to @c Target.
      //!
      //! @Effects Forwards the assignment to the reference using @c assign_to
      //! @Returns @c *this
      //! @Throws Whatever @c assign_to throws.
      //! @Remark This constructor doesn't participates on overload resolution if @c Source is not extrinsic assignable to @c Target.
      template <typename Source>
#if defined(BOOST_CONVERSION_ENABLE_CND) && !defined(BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)
      typename boost::enable_if< boost::is_extrinsic_assignable<Target,Source>, assignable_to& >::type
#else
      assignable_to&
#endif
      operator =(Source const& u)
      {
        boost::conversion::assign_to(ref_, u);
        return *this;
      }
    };
    //! makes an assignable to @c Target.

    //! The result is able to transform conversion by convert_to calls and assignments by assign_to calls.
    //! @NoThrow.
    template <typename Target>
    assignable_to<Target> mat(Target& r)
    {
      return assignable_to<Target>(r);
    }
  }
}

#endif

