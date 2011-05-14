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

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(conversion)(fp)(convert_to)
  , (proto::terminal<boost::phoenix::detail::target<proto::_> >)
    (boost::phoenix::meta_grammar)
)

namespace boost { 
  namespace conversion {
    namespace fp {
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
          return boost::convert_to<
          typename boost::phoenix::detail::result_of::target<Target>::type
          >(boost::phoenix::eval(u, ctx));
        }
      };
    }
  }

  namespace phoenix {
    template <typename Dummy>
    struct default_actions::when<boost::conversion::fp::rule::convert_to, Dummy>
    : call<boost::conversion::fp::convert_to_eval, Dummy>
    {};

  }
  namespace conversion {
    namespace fp {
  
      template <typename T, typename U>
      inline
      typename expression::convert_to<boost::phoenix::detail::target<T>, U>::type const
      convert_to(U const& u)
      {
        return
        expression::
        convert_to<boost::phoenix::detail::target<T>, U>::
        make(boost::phoenix::detail::target<T>(), u);
      }
    }
  }
}

#endif
