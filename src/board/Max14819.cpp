//!*****************************************************************************
//! \file   Max14819.cpp
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

#include "protocol/IOLMasterPort.hpp"

#include "Max14819.hpp"
#include "Max14819_Port.hpp"

// TODO centralize include management
#ifdef ARDUINO
#include <stdint.h>
#include <stdio.h>
#else
#include <cstdint>
#include <cstdio>
#endif

namespace openiolink // TODO ::PCB?
{
    // TODO removable?
    //! \name Commands to read or write registers
    //!\{
    static constexpr uint8_t read = 0b00000001;  //!< read command
    static constexpr uint8_t write = 0b01111111; //!< write command
                                                 //!\}

    // -------------------------------------------------------------------------

    //!*****************************************************************************
    //! \brief  Construct a new Max14819 object
    //!
    //! \param portA    reference to the first Max14819_Port object
    //!
    //! \param portB    reference to the second Max14819_Port object
    //!
    //!*****************************************************************************
    //template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
    //Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::Max14819(Max14819_Port<ChAPortNr> &portA,
    template <int ChipNr>
    Max14819<ChipNr>::Max14819(Max14819_Port<ChAPortNr> &portA,
                               Max14819_Port<ChBPortNr> &portB)
        : mPortA{portA}, mPortB{portB}
    {
        initGPIOs();
        SPI::init();
        configure(); // needs SPI
    }

    //!*****************************************************************************
    //! \brief  Destruct the Max14819 object
    //!
    //!*****************************************************************************
    //template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
    //Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::~Max14819()
    template <int ChipNr>
    Max14819<ChipNr>::~Max14819()
    {
    }

    //!*****************************************************************************
    //! \brief Reads data from register
    //!
    //!
    //! \param reg register definition
    //!
    //! \return uint8_t byte read from the register
    //!
    //!*****************************************************************************
    //template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
    //uint8_t Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::readRegister(uint8_t reg)
    template <int ChipNr>
    uint8_t Max14819<ChipNr>::readRegister(uint8_t reg)
    {
        uint8_t channel = 0;
        uint8_t buf[2];

        // Check if register address is in the correct range
        if (reg > MAX_REG)
        {
            // FIXME
            //debug_interface->print("Registeraddress out of range");
            return ERROR;
        }
        // Mask read register with the read cmd and set spi address of the max14819
        reg = reg | (read << 7) | (spi_address << 5);

        // Predefine buffer
        buf[0] = reg;
        buf[1] = 0x00;

        // Send the device the register you want to read:
        SPI::DataRW(buf, 2);

        // Return Registervalue
        return buf[1];
    }

    //!*****************************************************************************
    //! \brief Writes data into an register
    //!
    //!
    //! \param reg register definition
    //!
    //! \param data byte to write
    //!
    //! \return uint8_t 0 if success
    //!
    //!*****************************************************************************
    //template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
    //uint8_t Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::writeRegister(uint8_t reg, uint8_t data)
    template <int ChipNr>
    uint8_t Max14819<ChipNr>::writeRegister(uint8_t reg, uint8_t data)
    {
        uint8_t retValue = SUCCESS;
        uint8_t buf[2];

        // Check if register address is in the correct range
        if (reg > MAX_REG)
        {
            // FIXME
            //debug_interface->print("Registeraddress out of range");
            return ERROR;
        }
        // Set write bit in register command
        reg &= write;
        reg |= (spi_address << 5);

        // Send SPI telegram
        buf[0] = reg;
        buf[1] = data;
        SPI::DataRW(buf, 2);

        // Return Error state
        return retValue;
    }

    //!*****************************************************************************
    //! \brief  Initializes the GPIOs that are associated to the chip.
    //!
    //!*****************************************************************************
    //template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
    //void Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::initGPIOs()
    template <int ChipNr>
    void Max14819<ChipNr>::initGPIOs()
    {
        IRQPin::init();
        CSPin::init();
        CSPin::setHigh(); // deassert (chip select is low-active)
    }

    //!*****************************************************************************
    //! \brief  Configures the chip
    //! \todo   Move code from OpeniolinkShieldHat::configureBothMax14819() to here.
    //!
    //!*****************************************************************************
    //template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
    //void Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::configure()
    template <int ChipNr>
    void Max14819<ChipNr>::configure()
    {
    }

    //!*****************************************************************************
    //! \brief  Resets the whole chip
    //!
    //! \return uint8_t 0 if success
    //!
    //!*****************************************************************************
    //template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
    //uint8_t Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::reset()
    template <int ChipNr>
    uint8_t Max14819<ChipNr>::reset()
    {
        uint8_t retValue = SUCCESS;
        // Reset all max14819 registers
        retValue = writeRegister(ChanStatA, Rst);
        retValue = uint8_t(retValue | writeRegister(ChanStatB, Rst));
        retValue = uint8_t(retValue | writeRegister(InterruptEn, 0));
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, 0));
        retValue = uint8_t(retValue | writeRegister(Trigger, 0));
        retValue = uint8_t(retValue | writeRegister(DrvrCurrLim, 0));
        // Return Error state
        return retValue;
    }

} // namespace openiolink // TODO ::PCB?
