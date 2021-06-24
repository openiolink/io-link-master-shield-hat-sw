//!*****************************************************************************
//!  \file MapperChip.hpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief Struct template to configure associations to a Transceiver chip which
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

#ifndef MAPPERCHIP_SHIELDHAT_HPP
#define MAPPERCHIP_SHIELDHAT_HPP

// platform-specific headers
#ifdef ARDUINO
#include "arduino/MapperChip_Arduino.hpp"
#else
#ifdef RASPBERRY
#include "raspberry/MapperChip_Raspberry.hpp"
#else
static_assert(false, "no known platform defined");
#endif
#endif

// generic (other) headers
#include <iostream> // uint8_t
#include "MapperSpi.hpp"
#include "platform.hpp" // namespace platform

namespace openiolink
{
    namespace shield_hat_x // TODO make unnamed namespace to avoid access from any other translation unit
    {
        // TODO Doc
        template <int ChipNr>
        struct MapperChip
        {
        };

        // Configuration for chip 0
        template <>
        struct MapperChip<0>
        {
            static constexpr uint8_t SPIAddress = 0x00;
            static constexpr int SPINr = 0;
            using SPI = MapperSpi<SPINr>::SPI;
        };

        // Configuration for chip 1
        template <>
        struct MapperChip<1>
        {
            static constexpr uint8_t SPIAddress = 0x02;
            static constexpr int SPINr = 1;
            using SPI = MapperSpi<SPINr>::SPI;
        };
    }

    // TODO Doc
    template <int ChipNr>
    struct MapperChip
    {
        static constexpr uint8_t SPIAddress = shield_hat_x::MapperChip<ChipNr>::SPIAddress;
        static constexpr int SPINr = shield_hat_x::MapperChip<ChipNr>::SPINr;
        using SPI = shield_hat_x::MapperChip<ChipNr>::SPI;
        static constexpr int CSPinNr = platform::MapperChip<ChipNr>::CSPinNr;
        static constexpr int IRQPinNr = platform::MapperChip<ChipNr>::IRQPinNr;
    };

    // TODO Doc
    //TODO make sure that MapperIOLPort<Ch1IOLPortNr>::ChipNr == MapperIOLPort<Ch2IOLPortNr>::ChipNr == ChipNr
    template <int ChipNr>
    struct BackMapperChip
    {
    };

    // Configuration for chip 0
    template <>
    struct BackMapperChip<0>
    {
        static constexpr int Ch1IOLPortNr = 0;
        static constexpr int Ch2IOLPortNr = 1;
    };

    // Configuration for chip 1
    template <>
    struct BackMapperChip<1>
    {
        static constexpr int Ch1IOLPortNr = 2;
        static constexpr int Ch2IOLPortNr = 3;
    };

} // namespace openiolink

#endif // MAPPERCHIP_SHIELDHAT_HPP