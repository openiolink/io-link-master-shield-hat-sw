//!*****************************************************************************
//!  \file MapperSpi.hpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief Struct template to configure associations to an SPI interface which
//!         are valid for the "IO-Link-Master-Shield/Hat" from openiolink
//!         independent of the target plattform (e.g. Raspberry Pi or Arduino).
//!
//!  \date 2021-06-01
//!
//!
//!  *****************************************************************************
//!
//!  \copyright
//!  Copyright 2021 Bern University of Applied Sciences and Balluff AG
//!  \n\n
//!  Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!  \n\n
//!      http://www.apache.org/licenses/LICENSE-2.0
//!  \n\n
//!  Unless required by applicable law or agreed to in writing, software
//!  distributed under the License is distributed on an "AS IS" BASIS,
//!  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!  See the License for the specific language governing permissions and
//!  limitations under the License.
//!
//!*****************************************************************************

#ifndef MAPPERSPI_HPP
#define MAPPERSPI_HPP

#include "arduino/SpiArduino.hpp"     // TODO replace these two lines with one: #include "Spi.hpp"
#include "raspberry/SpiRaspberry.hpp" // TODO adjust board/CMakeLists.txt to add only one of the subdirectories of board/
#include "platform.hpp"

namespace openiolink
{
    template <int SPINr>
    struct MapperSpi
    {
        using SPI = platform::SPI<SPINr>;

        // If your Board Support Package library for SPI needs GPIO numbers for
        // MISO, MOSI, SCK, ... you should define them in
        //      yourplatform::MapperSpi
        // and then access them from here like this:
        //      static constexpr int MISOPinNr = platform::MapperSpi<SPINr>::MISOPinNr
        // DO NOT write hardcoded pinnumbers in this file (MapperSpi.hpp).
    };

} // namespace openiolink
#endif
