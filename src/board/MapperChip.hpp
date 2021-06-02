//!*****************************************************************************
//!  \file MapperChip.hpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief Struct template to configure associations to a Transceiver chip for 
//!         case when the "IO-Link-Master-Shield/Hat" from openiolink is used
//!         with an Arduino Due.
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

#ifndef ARDUINO_MAPPERCHIP_H
#define ARDUINO_MAPPERCHIP_H

#include "MapperChip_ShieldHat.hpp"

namespace openiolink::ARDUINO
{

    template <int ChipNr>
    struct MapperChip
    {
    };

    // Configuration for chip 0
    template <>
    struct MapperChip<0>
    {
        // independent of target platform (Arduino)
        static constexpr std::uint8_t SPIAddress = MapperChipShieldHat<0>::SPIAddress;
        static constexpr int SPINr = MapperChipShieldHat<0>::SPINr;
        using SPI = MapperChipShieldHat<0>::SPI;

        // specific for Arduino Due
        static constexpr int CSPinNr = 10u;
        static constexpr int IRQPinNr = 5u;
    };

    // Configuration for chip 1
    template <>
    struct MapperChip<1>
    {
        // independent of target platform (Arduino)
        static constexpr std::uint8_t SPIAddress = MapperChipShieldHat<0>::SPIAddress;
        static constexpr int SPINr = MapperChipShieldHat<0>::SPINr;
        using SPI = MapperChipShieldHat<0>::SPI;

        // specific for Arduino Due
        static constexpr int CSPinNr = 4u;
        static constexpr int IRQPinNr = 11u;
    };

    //------------------------------------------------------------------------------

    //TODO make sure that MapperIOLPort<Ch1IOLPortNr>::ChipNr == MapperIOLPort<Ch2IOLPortNr>::ChipNr == ChipNr
    template <int ChipNr>
    struct BackMapperChip
    {
    };
    
    // Configuration for chip 0
    template<>
    struct BackMapperChip<0>
    {
        static constexpr int Ch1IOLPortNr = 0;
        static constexpr int Ch2IOLPortNr = 1;
    };
    
    // Configuration for chip 1
    template<>
    struct BackMapperChip<1>
    {
        static constexpr int Ch1IOLPortNr = 2;
        static constexpr int Ch2IOLPortNr = 3;
    };
    

} // namespace openiolink::ARDUINO
#endif
