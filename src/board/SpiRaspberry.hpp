//!*****************************************************************************
//!  \file SpiRaspberry.hpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief API for SPI on Raspberry Pi
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

#include <iostream>
//FIXME
//#include <wiringPi.h>
//#include <wiringPiSPI.h> // Needed for SPI communication
//HACK
int wiringPiSPIDataRW(int, uint8_t *, const int);

#include "typedefs_board.hpp"

namespace openiolink::raspberry
{
    template <int SpiPort>
    class SPI
    {
    public:
        static bool init();
        static inline bool DataRW(uint8_t *data, const int length);

    private:
        static bool mInitDone;
    };

    template <int SpiPort>
    inline bool SPI<SpiPort>::DataRW(uint8_t *data, const int length)
    {
        wiringPiSPIDataRW(SpiPort, data, length); // FIXME: What does this function return?
        return BoolSuccess;
    }

} // namespace openiolink::raspberry