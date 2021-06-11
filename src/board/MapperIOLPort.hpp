//!*****************************************************************************
//!  \file MapperIOLPort.hpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief Struct template to configure the associations of the chip and the cannel
//!         to each IO-Link Port of the IO-Link-Master-Shield/Hat from openiolink
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

#ifndef MAPPERIOLPORT_HPP
#define MAPPERIOLPORT_HPP

#include "../platform.hpp"
#include "MapperIOLPort_Arduino.hpp"
#include "MapperIOLPort_Raspberry.hpp"

namespace openiolink
{
    namespace shield_hat
    {
        //!  ***********************************************************************
        //!
        //!  \brief Struct template to configure the associations of the chip and
        //!         the cannel to each IO-Link Port of the IO-Link-Master-Shield/Hat
        //!
        //!  ***********************************************************************
        template <int IOLPortNr>
        struct MapperIOLPort
        {
        };

        // Settings for IO-Link-Port 0 ("PORT0")
        template <>
        struct MapperIOLPort<0>
        {
            static constexpr int ChipNr = 0;
            static constexpr int ChannelNr = 0;
        };

        // Settings for IO-Link-Port 1 ("PORT1")
        template <>
        struct MapperIOLPort<1>
        {
            static constexpr int ChipNr = 0;
            static constexpr int ChannelNr = 1;
        };

        // Settings for IO-Link-Port 2 ("PORT2")
        template <>
        struct MapperIOLPort<2>
        {
            static constexpr int ChipNr = 1;
            static constexpr int ChannelNr = 0;
        };

        // Settings for IO-Link-Port 3 ("PORT3")
        template <>
        struct MapperIOLPort<3>
        {
            static constexpr int ChipNr = 1;
            static constexpr int ChannelNr = 1;
        };
    } // namespace shield_hat

    //!  ***********************************************************************
    //!
    //!  \brief Struct template to configure all neccessary associations to each
    //!         IO-Link Port of the IO-Link-Master-Shield/Hat
    //!
    //!  ***********************************************************************
    template <int IOLPortNr>
    struct MapperIOLPort
    {
        static constexpr int ChipNr = shield_hat::MapperIOLPort<IOLPortNr>::ChipNr; // geht bei Klassen sowieso nicht, würde die Variable pro CPP-Datei duplizieren
        // früher mit enums definiert
        static constexpr int ChannelNr = shield_hat::MapperIOLPort<IOLPortNr>::ChannelNr;
        static constexpr int DIPinNr = platform::MapperIOLPort<IOLPortNr>::DIPinNr;
        static constexpr int GreenLedPinNr = platform::MapperIOLPort<IOLPortNr>::GreenLedPinNr;
        static constexpr int RedLedPinNr = platform::MapperIOLPort<IOLPortNr>::RedLedPinNr;
        static constexpr int RxErrPinNr = platform::MapperIOLPort<IOLPortNr>::RxErrPinNr;
        static constexpr int RxRdyPinNr = platform::MapperIOLPort<IOLPortNr>::RxRdyPinNr;
    };

    template <int IOLPortNr>
    constexpr int MapperIOLPort<IOLPortNr>::ChipNr;//=shield_hat::MapperIOLPort<IOLPortNr>::ChipNr;
    // müsste ev. noch explizit instanziiert werden
    // besser Tests anpassen.

} // namespace openiolink

#endif // MAPPERIOLPORT_HPP
