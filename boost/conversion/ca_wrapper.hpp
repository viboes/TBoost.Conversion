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
 \file
 \brief
 Defines the free function @c mca.
 */
#ifndef BOOST_CONVERSION_CA_WRAPPER_HPP
#define BOOST_CONVERSION_CA_WRAPPER_HPP

#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
  namespace conversion {

    //! wrapper providing assignment and conversion operations from a reference.

    template <typename T>
    class ca_wrapper {
    public:
      T& ref_;
      //! copy constructor
      //! @NoThrow.
      ca_wrapper(ca_wrapper const& r) : ref_(r.ref_) { }

      //! constructor from a reference
      //! @NoThrow.
      ca_wrapper(T& r) : ref_(r) {}

      //! Implicit conversion to @c U.
      //! @Effects Forwards the conversion from the reference using @c conver_to.
      //! @Returns @c *this
      //! @Throws Whatever @c convert_to throws.
      template <typename U>
      operator U() {
        return boost::conversion::convert_to<U>(ref_);
      }

      //! Assignment.
      //!
      //! @Effects Forwards the assignment to the reference.
      //! @Returns @c *this
      //! @Throws Whatever @c T assignment can throws.
      ca_wrapper& operator =(ca_wrapper<T> const& u) {
        ref_ = u.ref_;
        return *this;
      }

      //! Assignment from a converter assigner wrapping a type U  convertible to T.
      //!
      //! @Effects Forwards the assignment to the reference using assign_to.
      //! @Returns @c *this
      //! @Throws Whatever @c assign_to throws.
      template <typename U>
      ca_wrapper& operator =(ca_wrapper<U> const& u) {
        boost::conversion::assign_to(ref_, u.ref_);
        return *this;
      }

      //! Assignment from a type U convertible to T.
      //!
      //! @Effects Forwards the assignment to the reference using assign_to
      //! @Returns @c *this
      //! @Throws Whatever @c assign_to throws.
      template <typename U>
      ca_wrapper& operator =(U const& u) {
        boost::conversion::assign_to(ref_, u);
        return *this;
      }
    };
    //! makes a converter assigner wrapper of the reference parameter.

    //! The result is able to transform conversion by convert_to calls and assignments by assign_to calls.
    //! @NoThrow.
    template <typename T>
    ca_wrapper<T> mca(T& r) {
      return ca_wrapper<T>(r);
    }
  }
}

#endif

