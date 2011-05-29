//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/*!
 \file
 \brief
 Defines the free function @c try_assign_to.

The function @c try_assign_to assigns the @c from parameter to the @c to parameter. Return @c true if assignation done and @c false otherwise.
The default implementation applies the the assignment operator of the @c To class.
A user adapting another type could need to specialize the @c try_assign_to free function if the default behavior is not satisfactory ot if it can improve the performances

The user can add the @c try_assign_to overloading on the namespace of the Source or Target classes.
But sometimes as it is the case for the standard classes, we can not add new functions on the std namespace,
so we need a different technique.

The technique consists in partially specialize on the function @c try_assign_to on the @c boost::conversion namespace.
For compilers for which we can not partially specialize a function a trick is used:
instead of calling directly to the @c try_assign_to member function, @c try_assign_to calls to the static operation apply
on a class with the same name in the namespace @c overload_workaround.
Thus the user can specialize partially this class.

 */

#ifndef BOOST_CONVERSION_TRY_ASSIGN_TO_HPP
#define BOOST_CONVERSION_TRY_ASSIGN_TO_HPP

#include <cstddef> //for std::size_t
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>

namespace boost {
  namespace conversion {
    namespace overload_workaround {
      //! <c>struct try_assign_to</c> used when overloading can not be applied.
      //! This struct can be specialized by the user.
      template < typename To, typename From >
      struct try_assign_to
      {
        //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
        //! @NoThrows  
        //! @Return the converted value if success or the fallback when conversion fails.
        inline static bool apply(To& to, const From& from)
        {
          To rollback = to;
          try 
          {
            to = from;
            return true;
          } 
          catch (...)
          {
            to = rollback; 
            return false;
          }
        }
      };
      template < typename To, typename From, std::size_t N  >
      struct try_assign_to<To[N],From[N]>
      {
        //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator on each vector element.
        //! @NoThrows  
        //! @Return the converted value if success or the fallback when conversion fails.
        inline static bool apply(To(&to)[N], const From(& from)[N])
        {
          To rollback[N];
          boost::conversion::assign_to<To>(rollback, to);
          try 
          {
            for (std::size_t i = 0; i < N; ++i)
            {
              boost::conversion::assign_to<To>(to[i] , from[i]);
            }
            return true;
          } 
          catch (...)
          {
            boost::conversion::assign_to<To>(to, rollback);
            return false;
          }
        }
      };
    }


#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    namespace impl_2 {
      //! @brief Default @c try_assign_to overload, used when ADL fails.
      //!
      //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
      //! @NoThrows
      //! @Return the converted value if success or the fallback when conversion fails.
      //! Forwards the call to the overload workaround, which can yet be specialized by the user for standard C++ types.
      template < typename To, typename From >
      bool try_assign_to(To& to, const From& from, dummy::type_tag<To> const&)
      {
        return conversion::overload_workaround::try_assign_to<To,From>::apply(to, from);
      }
    }

    namespace impl {
      template <typename Target, typename Source>
      bool try_assign_to_impl(Target& to, const Source& from)
      {
        using namespace boost::conversion::impl_2;
        //use boost::conversion::try_assign_to if ADL fails
        return try_assign_to(to, from, dummy::type_tag<Target>());
      }
    }
#endif

    //! @Effects  Converts the @c from parameter to  the @c to parameter, using by default the assignment operator.
    //! @NoThrows
    //! @Return the converted value if success or the fallback when conversion fails.
    //!
    //! This function can be partially specialized on compilers supporting it.
    template <typename Target, typename Source>
    bool try_assign_to(Target& to, const Source& from, dummy::base_tag<Target> const& p=dummy::base_tag<Target>()
    )
    {
      (void)p;
      return conversion::impl::try_assign_to_impl<Target, Source>(to, from);
    }
  }
}

#endif

