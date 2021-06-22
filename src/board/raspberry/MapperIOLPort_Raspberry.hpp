//!*****************************************************************************
//!  \file MapperIOLPort_Raspberry.hpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief Struct template to configure associations to each IO-Link Port of the
//!         IO-Link-Master-Shield/Hat from openiolink when used with a Raspberry Pi 3
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

#ifndef RASPBERRY_MAPPERIOLPORT_HPP
#define RASPBERRY_MAPPERIOLPORT_HPP

namespace openiolink
{
    namespace raspberry
    {
        template <int IOLPortNr>
        struct MapperIOLPort
        {
        };

        // Settings for IO-Link-Port 0 ("PORT0")
        template <>
        struct MapperIOLPort<0>
        {
            static constexpr int DIPinNr = 7u;
            static constexpr int GreenLedPinNr = 9u;
            static constexpr int RedLedPinNr = 8u;
            static constexpr int RxErrPinNr = 23u;
            static constexpr int RxRdyPinNr = 24u;
        };

        // Settings for IO-Link-Port 1 ("PORT1")
        template <>
        struct MapperIOLPort<1>
        {
            static constexpr int DIPinNr = 15u;
            static constexpr int GreenLedPinNr = 21u;
            static constexpr int RedLedPinNr = 22u;
            static constexpr int RxErrPinNr = 2u;
            static constexpr int RxRdyPinNr = 3u;
        };

        // Settings for IO-Link-Port 2 ("PORT2")
        template <>
        struct MapperIOLPort<2>
        {
            static constexpr int DIPinNr = 16u;
            static constexpr int GreenLedPinNr = 25u;
            static constexpr int RedLedPinNr = 1u;
            static constexpr int RxErrPinNr = 27u;
            static constexpr int RxRdyPinNr = 26u;
        };

        // Settings for IO-Link-Port 3 ("PORT3")
        template <>
        struct MapperIOLPort<3>
        {
            static constexpr int DIPinNr = 30u;
            static constexpr int GreenLedPinNr = 29u;
            static constexpr int RedLedPinNr = 5u;
            static constexpr int RxErrPinNr = 6u;
            static constexpr int RxRdyPinNr = 28u;
        };

    } // namespace raspberry
} // namespace openiolink

#endif // RASPBERRY_MAPPERIOLPORT_HPP
