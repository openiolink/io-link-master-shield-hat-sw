//!*****************************************************************************
//! \file   MapperChip_Arduino.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//! \brief  Struct template to configure pin associations to each transceiver
//!         chip on the IO-Link-Master-Shield/Hat from openiolink when used with
//!         an Arduino DUE.
//!
//! \date   2021-06-02
//!
//! \note   This .hpp file has no associated .cpp file.
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
#ifndef MAPPERCHIP_ARDUINO_HPP
#define MAPPERCHIP_ARDUINO_HPP

namespace openiolink
{
    namespace arduino
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
            static constexpr int CSPinNr = 10u;
            static constexpr int IRQPinNr = 5u;
        };

        // Configuration for chip 1
        template <>
        struct MapperChip<1>
        {
            static constexpr int CSPinNr = 4u;
            static constexpr int IRQPinNr = 11u;
        };

    } // namespace arduino
} // namespace openiolink

#endif // MAPPERCHIP_ARDUINO_HPP
