//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[SWAP_CPP

    #include <boost/conversion/assign_to.hpp>
    #include <iostream>
    using namespace boost::conversion;

    template <typename T, typename U>
    void swap_convertibles(T& t, U& u)
    {
      T tmp(t);
      assign_to(t,u);
      assign_to(u,tmp);
    }
    int main()
    {
      int i = 3;
      float x = 2.5;

      std::cout << "i= " << i << std::endl;
      std::cout << "x= " << x << std::endl;

#if defined(BOOST_CONVERSION_ENABLE_CND)
      swap_convertibles(i, x);
#endif

      std::cout << "i= " << i << std::endl;
      std::cout << "x= " << x << std::endl;
      return 0;
    }


//]
