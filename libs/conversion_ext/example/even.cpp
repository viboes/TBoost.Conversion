//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2008-2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[EVEN_CPP

    #include <boost/conversion/convert_to.hpp>
    #include <boost/conversion/std/string.hpp>
    #include <iostream>
    using namespace boost::conversion;

    template <typename T>
    bool is_even(T val)
    {
      return (convert_to<int>(val) % 2)==0;
    }
    int main()
    {
      std::string str = "2";
      if (is_even(str))
        std::cout << "2 is even" << std::endl;
      else
        std::cout << "2 is odd" << std::endl;

      return 0;
    }

//]
