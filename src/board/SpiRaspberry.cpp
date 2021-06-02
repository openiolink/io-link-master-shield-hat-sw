//!*****************************************************************************
//!  \file SpiRaspberry.cpp
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

#include "SpiRaspberry.hpp"     // the header of this class
#include "typedefs_board.hpp"
#include <wiringPi.h>
#include <wiringPiSPI.h>		// Needed for SPI communication
#include <fcntl.h>   			// Needed for SPI port
#include <sys/ioctl.h>			// Needed for SPI port
#include <linux/spi/spidev.h>	// Needed for SPI port

namespace raspberry
{
    // NOTE: on Raspberry Pi, we use both SPI channels that are available

    template <int SpiPort>
    bool SPI<SpiPort>::init()
    {
        static_assert(SpiPort == 0 || SpiPort == 1);

        if (!mInitDone)
        {
            wiringPiSPISetup(SpiPort, spi_speed);
            mInitDone = true;
        }
        return BoolSuccess;
    }

    } // namespace raspberry
