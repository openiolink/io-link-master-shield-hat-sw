//!*****************************************************************************
//!  \file MapperIOLPort.hpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief Struct template to configure associations to each IO-Link Port of the
//!         IO-Link-Master-Shield/Hat from openiolink when used with an Arduino DUE
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
#ifndef ARDUINO_MAPPERIOLPORT_HPP
#define ARDUINO_MAPPERIOLPORT_HPP

namespace openiolink
{
    namespace arduino
    {
        template <int IOLPortNr>
        struct MapperIOLPort
        {
        };

        // Settings for IO-Link-Port 0 ("PORT0")
        template <>
        struct MapperIOLPort<0>
        {
            static constexpr int DIPinNr = 55u;
            static constexpr int GreenLedPinNr = 2u;
            static constexpr int RedLedPinNr = 3u;
            static constexpr int RxErrPinNr = 61u;
            static constexpr int RxRdyPinNr = 60u;
        };

        // Settings for IO-Link-Port 1 ("PORT1")
        template <>
        struct MapperIOLPort<1>
        {
            static constexpr int DIPinNr = 54u;
            static constexpr int GreenLedPinNr = 56u;
            static constexpr int RedLedPinNr = 57u;
            static constexpr int RxErrPinNr = 58u;
            static constexpr int RxRdyPinNr = 59u;
        };

        // Settings for IO-Link-Port 2 ("PORT2")
        template <>
        struct MapperIOLPort<2>
        {
            static constexpr int DIPinNr = 14u;
            static constexpr int GreenLedPinNr = 6u;
            static constexpr int RedLedPinNr = 7u;
            static constexpr int RxErrPinNr = 9u;
            static constexpr int RxRdyPinNr = 8u;
        };

        // Settings for IO-Link-Port 3 ("PORT3")
        template <>
        struct MapperIOLPort<3>
        {
            static constexpr int DIPinNr = 15u;
            static constexpr int GreenLedPinNr = 71u;
            static constexpr int RedLedPinNr = 70u;
            static constexpr int RxErrPinNr = 13u;
            static constexpr int RxRdyPinNr = 12u;
        };

    } // namespace arduino
} // namespace openiolink

#endif // ARDUINO_MAPPERIOLPORT_HPP
