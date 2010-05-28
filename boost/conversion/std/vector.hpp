//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[VECTOR__HPP
#ifndef BOOST_CONVERT_TO_PAIR__HPP
#define BOOST_CONVERT_TO_PAIR__HPP

#include <vector>
#include <boost/conversion/convert_to.hpp>
#include <boost/conversion/assign_to.hpp>
#include <boost/conversion/pack.hpp>


namespace boost { namespace conversion {

    namespace partial_specialization_workaround {
        template < class T1, class A1, class T2, class A2>
        struct convert_to< std::vector<T1,A1>, std::vector<T2,A2> > {
            inline static std::vector<T1,A1> apply(std::vector<T2,A2> const & from)
            {
                std::vector<T1,A1> res;
                boost::assign_to(res, from);
                return res;
            }
        };
        template < class T1, class A1, class T2, class A2>
        struct assign_to< std::vector<T1,A1>, std::vector<T2,A2> > {
            inline static std::vector<T1,A1>& apply(
                std::vector<T1,A1>& to, 
                std::vector<T2,A2> const & from)
            {
                to.resize(from.size());
                for (unsigned int i=0; i<from.size(); ++i) {
                    boost::assign_to(to[i], from[i]);
                }
                return to;
            }
        };
        
        template < class T1, class A1, class T2, class A2>
        struct convert_to< std::vector<T1,A1>, 
                std::pair<
                    boost::reference_wrapper<std::vector<T2,A2> const>, 
                    boost::reference_wrapper<A1 const> 
                > 
            > {
            inline static std::vector<T1,A1> apply(
                std::pair<
                    boost::reference_wrapper<std::vector<T2,A2> const>, 
                    boost::reference_wrapper<A1 const> 
                > const & pack)
            {
                std::vector<T1,A1> res(fusion::at_c<1>(pack));
                boost::assign_to(res, fusion::at_c<0>(pack).get());
                return res;
            }
        };
        
    }
}}

#endif

//]
