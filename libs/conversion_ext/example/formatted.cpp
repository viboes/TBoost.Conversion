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

    #include <boost/conversion/extractor.hpp>
    #include <boost/conversion/std/string.hpp>
    #include <boost/conversion/convert_to_or_fallback.hpp>
    #include <strstream>
    #include <iostream>
    #include <string>
    #include <iomanip>
    #include <boost/assert.hpp>
    using namespace boost::conversion;

    int main()
    {
      std::string    hex_str = "FF"; // 255 in decimal
      std::stringstream ios;

      // This call fails
      int   bad = convert_to_or_fallback<int>(hex_str, -1);
      BOOST_ASSERT(bad == -1); // Failed decimal conversion from "FF"

      // Apply hex formatting while converting from string
      int i = convert_to<int>(extractor<int>(
          (ios.clear(), ios << hex_str, ios >> std::hex)));
      BOOST_ASSERT(i == 255); // Successful hex conversion from "FF"

      // Apply hex formatting while converting from string

      int ii = convert_to<int>(extractor_stream<int>() << hex_str >> std::hex >> extract);
      BOOST_ASSERT(ii == 255); // Successful hex conversion from "FF"

      int iii = convert_to<int>(extractor_stream<int>() << hex_str >> std::hex);
      BOOST_ASSERT(iii == 255); // Successful hex conversion from "FF"

#if 0
      // Apply hex, uppercase, showbase formatting while converting to string
      std::string si = convert_to<std::string>(extractor<std::string>(
          (ios.clear(), ios << std::showbase << std::uppercase << std::hex << i, ios)));
      BOOST_ASSERT(si == "0XFF");

      {
      std::string double_str = "1.2345e-02";
      std::stringstream ios;
      double d = convert_to<double>(extractor<double>(
          (ios.clear(), ios << double_str, ios >> std::setprecision(4) >> std::scientific)));

      std::string sd= convert_to<std::string>(extractor<std::string>(
           (ios.clear(), ios << std::setprecision(4) << std::scientific << d, ios)));

      BOOST_ASSERT(sd == double_str);
      }
#endif
      return 0;
    }

//]
