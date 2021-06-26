//!*****************************************************************************
//! \file   Max14819.hpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!         based on the work of Janik Lehmann (CrazyGecko) and Pascal Frei (freip2)
//!
//! \brief  Class for the maxim integrated Dual IO-Link Master Transceiver
//!         MAX14819
//!
//! \date   2021-06-18
//!
//!
//! *****************************************************************************
//!
//! \copyright
//! Copyright 2020 Bern University of Applied Sciences and Balluff AG
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
#ifndef MAX14819_HPP_INCLUDED
#define MAX14819_HPP_INCLUDED

// platform-specific headers
#ifdef ARDUINO
#include "arduino/Pin_Arduino.hpp"
#else
#ifdef RASPBERRY
#include "raspberry/Pin_Raspberry.hpp"
#else
static_assert(false, "no known platform defined");
#endif
#endif

// generic (other) headers
#include "Max14819_Base.hpp"
#include "protocol/IOLMasterPort.hpp"
#include "protocol/IOLMessage.hpp"
#include "protocol/IOLinkConfig.hpp"
#include "MapperChip.hpp"
#include "typedefs_board.hpp" // BoolSuccess and BoolError

namespace openiolink // TODO ::PCB?
{
    // forward declaration to avoid including "Max14819_Port.hpp" (which would
    // result in a cyrcle dependency)
    template <int PortNr>
    class Max14819_Port;

    static constexpr uint8_t ERROR = static_cast<uint8_t>(BoolError);     //!< return value for errors
    static constexpr uint8_t SUCCESS = static_cast<uint8_t>(BoolSuccess); //!< return value for success

    //!*****************************************************************************
    //! \brief  Class for the maxim integrated Dual IO-Link Master Transceiver
    //!         MAX14819
    //!
    //! \note   When referencing this class you MUST give the first template
    //!         parameter (ChipNr) only!
    //!
    //!*****************************************************************************
    template <int ChipNr> //,
                          //class SPI = typename MapperChip<ChipNr>::SPI,
                          //int ChAPortNr = BackMapperChip<ChipNr>::Ch1IOLPortNr,
                          //int ChBPortNr = BackMapperChip<ChipNr>::Ch2IOLPortNr>
    class Max14819 : Max14819_Base
    {
    private:
        static constexpr int ChAPortNr = BackMapperChip<ChipNr>::Ch1IOLPortNr; // was defaulted template parameter
        static constexpr int ChBPortNr = BackMapperChip<ChipNr>::Ch2IOLPortNr; // was defaulted template parameter

    public:
        Max14819(Max14819_Port<ChAPortNr> &portA, Max14819_Port<ChBPortNr> &portB);
        ~Max14819();
        uint8_t readRegister(uint8_t reg);
        uint8_t writeRegister(uint8_t reg, uint8_t data);
        //auto &getPort(Max14819_Port::PortNr port);-> Max14819_Port<port>
        // would be complicated because parametrized. If getPort() is necessary,
        // (A) split it to seperate methods for each port/channel or (B) return a IOLMasterPort reference.

    public:                                           // TODO private?
        static constexpr uint8_t MAX_MSG_LENGTH = 64; //!< maximal number of bytes to send (according to max14819 FIFO length)

    private:
        using SPI = typename MapperChip<ChipNr>::SPI; // was defaulted template parameter
        static constexpr uint8_t spi_address = MapperChip<ChipNr>::SPIAddress;

        typedef platform::InputPin<MapperChip<ChipNr>::IRQPinNr> IRQPin; //!< Interrupt
        typedef platform::OutputPin<MapperChip<ChipNr>::CSPinNr> CSPin;  //!< ChipSelect

        Max14819_Port<ChAPortNr> &mPortA;
        Max14819_Port<ChBPortNr> &mPortB;

        void initGPIOs();
        void configure();
        uint8_t reset();

    }; // class Max14819

    ////!*****************************************************************************
    ////! \brief  Class for the maxim integrated Dual IO-Link Master Transceiver
    ////!         MAX14819 (alias)
    ////!
    ////!*****************************************************************************
    //template <int ChipNr>
    //using Max14819Alias = Max14819<ChipNr,
    //                               class SPI = typename MapperChip<ChipNr>::SPI,
    //                               int ChAPortNr = BackMapperChip<ChipNr>::Ch1IOLPortNr,
    //                               int ChBPortNr = BackMapperChip<ChipNr>::Ch2IOLPortNr>

} // namespace openiolink // TODO ::PCB?

// We need to include "our" .cpp file here. Explanation:
// Part of the methods of the class template declared in this .hpp file may be
// defined in the same-named .cpp file. Since these are template methods the
// compiler won't do anything when compiling the .cpp file, because he does not
// know the actual template parameter(s) (value or type) that will be given when
// the template is instatiated.
// Wherever this class template will be used (i.e. instantiated), the compiler
// will only have this .hpp at hand (assuming it was included), but lacks the
// implementation details (the definitions). Those are located in the .cpp and
// tis is why we include the .cpp file here.
// (There may be other solutions to this problem, see e.g.
// https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp)
#include "Max14819.cpp"
#endif //MAX14819_HPP_INCLUDED
