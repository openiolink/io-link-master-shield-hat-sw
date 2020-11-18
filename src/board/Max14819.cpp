//!*****************************************************************************
//!  \file Max14819.cpp
//!  
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!          based on the work of Pascal Frei (freip2)
//!  
//!  \brief Class for the maxim integrated Dual IO-Link Master Transceiver
//!         MAX14819
//!  
//!  \date 2020-11-18
//!  
//!  
//!  *****************************************************************************
//!  
//!  \copyright
//!  Copyright 2020 Bern University of Applied Sciences and Balluff AG
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

#include "protocol/IOLMasterPort.hpp"

#include "Max14819.hpp"

#ifdef ARDUINO
    #include <stdint.h>
	#include <stdio.h>
#else
    #include <cstdint>
	#include <cstdio>
#endif	

//! \name Commands to read or write registers
//!\{
constexpr uint8_t read = 0b00000001;
constexpr uint8_t write = 0b01111111;
//!\}

Max14819::Max14819(std::shared_ptr<DebugOut> debugout_, std::shared_ptr<SPI> spi_interface_, uint8_t spi_address_, std::shared_ptr<Wait> wait_) : debug_interface(debugout_), spi_interface(spi_interface_), spi_address(spi_address_), wait(wait_){
    debug_interface->print("Initialize Max");
}

Max14819::~Max14819() {

}

void Max14819::initPorts(void) // todo transform this to get ports
{
    char buffer[30];
    PORTA = std::make_shared<Max14819_Port>(Max14819_Port(Max14819_Port::PortNr::PORTA, shared_from_this()));
    PORTB = std::make_shared<Max14819_Port>(Max14819_Port(Max14819_Port::PortNr::PORTB, shared_from_this()));
}

uint8_t Max14819::reset(void) {
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
uint8_t Max14819::readRegister(uint8_t reg) {
    uint8_t channel = 0;
    uint8_t buf[2];

    // Check if register address is in the correct range
    if (reg > MAX_REG) {
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

uint8_t Max14819::writeRegister(uint8_t reg, uint8_t data) {
    uint8_t retValue = SUCCESS;
    uint8_t buf[2];

    // Check if register address is in the correct range
    if (reg > MAX_REG) {
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
    return retValue;;
}

uint8_t Max14819::Max14819_Port::sendIOLData(uint8_t* data, uint8_t sizeofdata, uint8_t sizeofanswer)
{
    uint8_t retValue = SUCCESS;
    uint8_t offset=0;
    // Todo remove offset and replace with enum
    if (portnr == PortNr::PORTB)
    {
        offset = 1; // PORTB Registers are 1 address higher than PORTA Register
    }

    retValue = uint8_t(retValue | chip->writeRegister(TxRxDataA + offset, sizeofanswer)); // number of bytes for answer
    retValue = uint8_t(retValue | chip->writeRegister(TxRxDataA + offset, sizeofdata)); // number of bytes for answer
    // send data
    for (uint8_t i = 0; i < sizeofdata; i++)
    {
        retValue = uint8_t(retValue | chip->writeRegister(TxRxDataA + offset, data[i]));
    }
    retValue = uint8_t(retValue | chip->writeRegister(CQCtrlA + offset, CQSend |communicationInfo.comSpeed));
    return retValue;
}

uint8_t Max14819::Max14819_Port::readIOLData(uint8_t* data, uint8_t sizeofdata) {
    uint8_t bufferRegister;
    uint8_t retValue = SUCCESS;
    // Use corresponding transmit FIFO address
    uint8_t offset=0;
    // Todo remove offset and replace with enum
    if (portnr == PortNr::PORTB)
    {
        offset = 1; // PORTB Registers are 1 address higher than PORTA Register
    }

    chip->wait->ms(10); // TODO another solution to wait for an iol answer should be implemented

    // Controll if the aswer has the expected length (first byte in the FIFO is the messagelength)
    if (sizeofdata != chip->readRegister(bufferRegister)) {
        // TODO Error Handling if Buffer is corrupted
        retValue = ERROR;
    }

    // Read data from FIFO
    for (uint8_t i = 0; i < sizeofdata; i++) {
        *data++ = chip->readRegister(bufferRegister);
    }
    // Return Error state
    return retValue;
}

void Max14819::Max14819_Port::setMode(Mode mode)
{
    // TODO set mode
}

void Max14819::Max14819_Port::wakeUpRequest()
{
    uint8_t retValue = 0;
    uint8_t comReqRunning = 0;
    uint8_t timeOutCounter = 0;
    uint16_t length = 0;
    uint8_t offset = 0;

    if (portnr == PortNr::PORTB)
    {
        offset = 1; // PORTB Registers are 1 address higher than PORTA Register
    }
    

    // Start wakeup and communcation
    retValue = uint8_t(retValue | chip->writeRegister(IOStCfgA + offset, 0)); // Disable tx needed for wake up
    retValue = uint8_t(retValue | chip->writeRegister(ChanStatA + offset, FramerEn)); // Enable ChanA Framer
    retValue = uint8_t(retValue | chip->writeRegister(MsgCtrlA + offset, 0)); // Dont use InsChks when transmit OD Data, max14819 doesnt calculate it right
    retValue = uint8_t(retValue | chip->writeRegister(CQCtrlA + offset, EstCom));     // Start communication

    // Wait till establish communication sequence is over or timeout is reached
    do {
        comReqRunning = chip->readRegister(CQCtrlA + offset);
        comReqRunning &= EstCom;
        timeOutCounter++;
        chip->wait->ms(1);
    } while (comReqRunning || (timeOutCounter < INIT_WURQ_TIMEOUT));

    chip->wait->ms(10);
    // Clear buffer
    length = chip->readRegister(RxFIFOLvlA + offset);
    for (uint8_t i = 0; i < length; i++) {
        chip->readRegister(TxRxDataA + offset);
    }

    // read communication speed
    communicationInfo.comSpeed = chip->readRegister(CQCtrlA + offset) & (ComRt0 | ComRt1);

    // Set correct communication speed in kBaud/s
    switch (communicationInfo.comSpeed) {
    case ComRt0:
        // Communication established at 4.8 kBaud/s
        communicationInfo.comSpeedBaud = 4800;
        break;
    case ComRt1:
        // Communication established at 38.4 kBaud/s
        communicationInfo.comSpeedBaud = 38400;
        break;
    case (ComRt0 | ComRt1):
        // Communication established at 230.4 kBaud/s
        communicationInfo.comSpeedBaud = 230400;
        break;
    default:
        // No communication established or other error occured
        communicationInfo.comSpeedBaud = 0;
        break;
    }
    chip->debug_interface->print("wurq done");
    // return SUCCESS;
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