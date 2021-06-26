//!*****************************************************************************
//! \file   SpiArduino.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  API for SPI on Arduino
//!
//! \date   2021-06-01
//!
//!
//! ****************************************************************************
//!
//! \copyright
//! Copyright 2021 Bern University of Applied Sciences and Balluff AG
//! \n\n
//! Licensed under the Apache License, Version 2.0 (the "License");
//! you may not use this file except in compliance with the License.
//! You may obtain a copy of the License at
//! \n\n
//!     http://www.apache.org/licenses/LICENSE-2.0
//! \n\n
//! Unless required by applicable law or agreed to in writing, software
//! distributed under the License is distributed on an "AS IS" BASIS,
//! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//! See the License for the specific language governing permissions and
//! limitations under the License.
//!
//!*****************************************************************************
#ifndef SPI_ARDUINO_HPP
#define SPI_ARDUINO_HPP

#include <iostream>

namespace openiolink
{
    namespace arduino
    {
        template <int SpiPort>
        class SPIClass
        {
        public:
            static bool init();
            static bool DataRW(uint8_t *data, const int length);

        private:
            static bool mInitDone;
        };

    } // namespace arduino
} // namespace openiolink

// We need to include "our" .cpp file here. Explanation:
// Part of the methods of the class template declared in this .hpp file may be
// defined in the same-named .cpp file. Since these are template methods the
// compiler won't do anything when compiling the .cpp file, because he does not
// know the actual template parameter(s) (value or type) that will be given when
// the template is instatiated.
// Wherever this class template will be used (i.e. instantiated), the compiler
// will only have this .hpp at hand (assuming it was included), but lacks the
// implementation details (the definitions). Those are located in the .cpp and
// tis is why we include the .cpp file here.
// (There may be other solutions to this problem, see e.g.
// https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp)
#include "SpiArduino.cpp"
#endif
