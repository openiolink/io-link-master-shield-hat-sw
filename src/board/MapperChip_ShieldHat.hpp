//!*****************************************************************************
//!  \file MapperChip_ShieldHat.hpp
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

#ifndef MAPPERCHIP_SHIELDHAT_H
#define MAPPERCHIP_SHIELDHAT_H

#include <iostream>
#include "MapperSpi.hpp"

namespace openiolink
{

    template <int ChipNr>
    struct MapperChipShieldHat
    {
    };

    // Configuration for chip 0
    template <>
    struct MapperChipShieldHat<0>
    {
        static constexpr uint8_t SPIAddress = 0x00;
        static constexpr int SPINr = 0;
        using SPI = MapperSpi<SPINr>::SPI;
    };

    // Configuration for chip 1
    template <>
    struct MapperChipShieldHat<1>
    {
        static constexpr uint8_t SPIAddress = 0x02;
        static constexpr int SPINr = 1;
        using SPI = MapperSpi<SPINr>::SPI;
    };

} // namespace openiolink

#endif // MAPPERCHIP_SHIELDHAT_H