//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONVERSION_FP_CONVERT_TO_HPP
#define BOOST_CONVERSION_FP_CONVERT_TO_HPP

#include <boost/conversion/convert_to.hpp>
#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>
#include <boost/phoenix/core/is_actor.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(conversion)(convert_to)
  , (proto::terminal<boost::phoenix::detail::target<proto::_> >)
    (boost::phoenix::meta_grammar)
)

#endif

namespace boost { 
  namespace conversion {

    //! @c enable_functor meta-function specialization for types @c T satisfying @c phoenix::is_actor<T>.

    //! The nested type @ type is @c mpl::true_.
    template <typename T>
    struct enable_functor<T, typename enable_if<phoenix::is_actor<T> >::type>  : mpl::true_ {};

    namespace detail {
      struct convert_to_eval
      {
        template <typename Sig>
        struct result;
        
        template <typename This, typename Target, typename Source, typename Context>
        struct result<This(Target const &, Source const&, Context)>
        : boost::phoenix::detail::result_of::target<Target>
        {};
        
        template <typename Target, typename Source, typename Context>
        typename boost::phoenix::detail::result_of::target<Target>::type
        operator()(Target, Source const& u, Context const& ctx) const
        {
          return boost::conversion::convert_to<
          typename boost::phoenix::detail::result_of::target<Target>::type
          >(boost::phoenix::eval(u, ctx));
        }
      };
    }
  }

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  namespace phoenix {

    //! specialization of @c phoenix::default_actions::when for the @c convert_to rule.
    template <typename Dummy>
    struct default_actions::when<boost::conversion::rule::convert_to, Dummy>
    : call<boost::conversion::detail::convert_to_eval, Dummy>
    {};

  }
#endif

  namespace conversion {

    //! @brief Lazily convert to a type @Target from an arbitrary argument.
    //!
    //! This overload of @convert_to is taken in account when the parameter @c Source is a place_holder.
    //!
    //! @Returns A unary functor that will call to the convert_to function on its parameter.
    //! @Throws  Whatever the underlying conversion @c To operator of the @c From class or the copy constructor of the @c To class throws.
    //! @Example
    //! @code
    //! boost::conversion::convert_to<int>(_1)(v);
    //! @endcode
    //! Creates a functor that when applied to the parameter v, converts it to an @c int.
    template <typename T, typename U>
    inline
#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
    typename enable_if<typename boost::conversion::enable_functor<U>::type,
      typename expression::convert_to<boost::phoenix::detail::target<T>, U>::type const
    >::type
#else
    typename expression::convert_to<boost::phoenix::detail::target<T>, U>::type const
#endif
    convert_to(U const& u)
    {
      return
      expression::
      convert_to<boost::phoenix::detail::target<T>, U>::
      make(boost::phoenix::detail::target<T>(), u);
    }
  }
}

#endif
