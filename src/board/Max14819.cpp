//!*****************************************************************************
//! \file   Max14819.cpp
//!
//! \author Tobias Gammeter (tobias.gammeter@gmail.com)
//!         based on the work of Janik Lehmann (CrazyGecko) and Pascal Frei (freip2)
//!
//! \brief  Class for the maxim integrated Dual IO-Link Master Transceiver
//!         MAX14819
//!
//! \date   2020-11-18
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

#ifdef ARDUINO
#include <stdint.h>
#include <stdio.h>
#else
#include <cstdint>
#include <cstdio>
#endif

//namespace openiolink // TODO ::PCB?
//{

//! \name Commands to read or write registers
//!\{
constexpr uint8_t read = 0b00000001;  //!< read command
constexpr uint8_t write = 0b01111111; //!< write command
//!\}

Max14819::Max14819(std::shared_ptr<DebugOut> debugout_, std::shared_ptr<SPI_Max14819> spi_interface_, uint8_t spi_address_, std::shared_ptr<Wait> wait_) : debug_interface(debugout_), spi_interface(spi_interface_), spi_address(spi_address_), wait(wait_)
{
    debug_interface->print("Initialize Max");
}

Max14819::~Max14819()
{
}

//template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
//inline Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::initPorts()
void Max14819::initPorts(void) // todo transform this to get ports
{
    char buffer[30];
    PORTA = std::make_shared<Max14819_Port>(Max14819_Port(Max14819_Port::PortNr::PORTA, shared_from_this()));
    PORTB = std::make_shared<Max14819_Port>(Max14819_Port(Max14819_Port::PortNr::PORTB, shared_from_this()));
}

////TODO take care that each chip is initialized at most once.
//template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
//void Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::init()
//{
//}

//template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
//inline Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::reset()
uint8_t Max14819::reset(void)
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

//template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
//inline Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::readRegister()
uint8_t Max14819::readRegister(uint8_t reg)
{
    uint8_t channel = 0;
    uint8_t buf[2];

    // Check if register address is in the correct range
    if (reg > MAX_REG)
    {
        debug_interface->print("Registeraddress out of range");
        return ERROR;
    }
    // Mask read register with the read cmd and set spi address of the max14819
    reg = reg | (read << 7) | (spi_address << 5);

    // Predefine buffer
    buf[0] = reg;
    buf[1] = 0x00;

    // Send the device the register you want to read:
    spi_interface->DataRW(buf, 2);

    // Return Registervalue
    return buf[1];
}

//template <int ChipNr, class SPI, int ChAPortNr, int ChBPortNr>
//inline Max14819<ChipNr, SPI, ChAPortNr, ChBPortNr>::writeRegister()
uint8_t Max14819::writeRegister(uint8_t reg, uint8_t data)
{
    uint8_t retValue = SUCCESS;
    uint8_t buf[2];

    // Check if register address is in the correct range
    if (reg > MAX_REG)
    {
        debug_interface->print("Registeraddress out of range");
        return ERROR;
    }
    // Set write bit in register command
    reg &= write;
    reg |= (spi_address << 5);

    // Send SPI telegram
    buf[0] = reg;
    buf[1] = data;
    spi_interface->DataRW(buf, 2);

    // Return Error state
    return retValue;
}

std::shared_ptr<Max14819::Max14819_Port> Max14819::getPort(Max14819_Port::PortNr port)
{
    switch (port)
    {
    case Max14819_Port::PortNr::PORTA:
        return PORTA;
        break;
    case Max14819_Port::PortNr::PORTB:
        return PORTB;
        break;

    default:
        return nullptr;
        break;
    }
}
//} // namespace openiolink // TODO ::PCB?
