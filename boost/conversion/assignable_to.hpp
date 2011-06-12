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

      //! Implicit conversion to @c U.
      //! @Effects Forwards the conversion from the reference using @c conver_to.
      //! @Returns @c *this
      //! @Throws Whatever @c convert_to throws.
      template <typename U>
      operator U()
      {
        return boost::conversion::convert_to<U>(ref_);
      }

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

      //! Assignment from a converter assigner wrapping a type U  convertible to Target.
      //!
      //! @Effects Forwards the assignment to the reference using assign_to.
      //! @Returns @c *this
      //! @Throws Whatever @c assign_to throws.
      template <typename U>
      assignable_to& operator =(assignable_to<U> const& u)
      {
        boost::conversion::assign_to(ref_, u.ref_);
        return *this;
      }

      //! Assignment from a type Source assignable to Target.
      //!
      //! @Effects Forwards the assignment to the reference using assign_to
      //! @Returns @c *this
      //! @Throws Whatever @c assign_to throws.
      template <typename Source>
      assignable_to& operator =(Source const& u)
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

