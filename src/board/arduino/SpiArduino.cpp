//!*****************************************************************************
//!  \file SpiArduino.cpp
//!
//!  \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!
//!  \brief API for SPI on Arduino
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

#include "SpiArduino.hpp"     // the header of this class
#include "../typedefs_board.hpp" //
#include <Arduino.h>          // Arduino library
#include <SPI.h>              // SPI for Arduino
#include <iostream>           // for uint8_t

namespace arduino
{
    // NOTE: Arduino DUE has only one SPI port
    /*
    TODO Documentation
    */
    template <int SpiPort>
    bool SPI<SpiPort>::init()
    {
        return BoolError;
        //return SPI<0>::init();
    }
    /*
    TODO Documentation
    */
    template <>
    bool SPI<0>::init()
    {
        if (!mInitDone)
        {
            SPI.begin();
            SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
            mInitDone = true;
        }
        return BoolSuccess;
    }

    /*
    TODO Documentation
    */
    template <int SpiPort>
    bool DataRW(uint8_t *data, const int length) const
    {
        // Arduino DUE has only one SPI port, make sure only this one is used
        static_assert(SpiPort==0);

        // simultaneously transmit and receive each byte
        // TODO Isn't a buffer transceive operation also possible (see https://www.arduino.cc/en/Reference/SPITransfer)?
        for (int i = 0; i < length; i++)
        {
            data[i] = SPI.transfer(data[i]);
        }
        return BoolSuccess;
    }

} // namespace arduino
