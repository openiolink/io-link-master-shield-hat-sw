//!*****************************************************************************
//!  \file MapperChip_Raspberry.hpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief Struct template to configure pin associations to each transceiver chip
//!         on the IO-Link-Master-Shield/Hat from openiolink when used with a
//!         Raspberry Pi 3.
//!
//!  \date 2021-06-02
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

#ifndef MAPPERCHIP_RASPBERRY_HPP
#define MAPPERCHIP_RASPBERRY_HPP

namespace openiolink::raspberry
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
        static constexpr int CSPinNr = 31u;
        static constexpr int IRQPinNr = 0u;
    };

    // Configuration for chip 1
    template <>
    struct MapperChip<1>
    {
        static constexpr int CSPinNr = 31u;
        static constexpr int IRQPinNr = 4u;
    };

} // namespace openiolink::raspberry

#endif // MAPPERCHIP_RASPBERRY_HPP
