
//!*****************************************************************************
//!  \file      Max14819.cpp
//!*****************************************************************************
//!
//!  \brief		max14819 driver specific layer
//!
//!  \author    Pascal Frei (freip2)
//!
//!  \date      2019-06-27
//!
//!*****************************************************************************
//!
//!	 Copyright 2019 Bern University of Applied Sciences and Balluff AG
//!
//!	 Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!
//!	     http://www.apache.org/licenses/LICENSE-2.0
//!
//!	 Unless required by applicable law or agreed to in writing, software
//!	 distributed under the License is distributed on an "AS IS" BASIS,
//!	 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!	 See the License for the specific language governing permissions and
//!	 limitations under the License.
//!	
//!*****************************************************************************

//!**** Header-Files ************************************************************
#include "protocol/IOLMasterPort.hpp"

#include "Max14819.hpp"

#ifdef ARDUINO
    #include <stdint.h>
	#include <stdio.h>
#else
    #include <cstdint>
	#include <cstdio>
#endif	

//!**** Macros ******************************************************************
constexpr uint8_t read = 0b00000001;
constexpr uint8_t write = 0b01111111;

//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************
uint8_t calculateCKT(uint8_t mc, uint8_t *data, uint8_t dataSize, uint8_t type);

//!**** Data ********************************************************************

//!**** Implementation **********************************************************

//!******************************************************************************
//!  function :    	max14819() constructor
//!******************************************************************************
//!  \brief        	Initialize the communication interface for the max14819.
//!
//!  \type         	local
//!
//!  \param[in]     void
//!
//!  \return        void
//!
//!******************************************************************************
Max14819::Max14819(std::shared_ptr<DebugOut> debugout_, std::shared_ptr<SPI> spi_interface_, uint8_t spi_address_) : debug_interface(debugout_), spi_interface(spi_interface_), spi_address(spi_address_){
    Max14819();
}

Max14819::Max14819(){
    debug_interface->print("Initialize Max");
}

// }
//!******************************************************************************
//!  function :    	~max14819() destructor
//!******************************************************************************
//! \brief        	Reset the communication interface for the max14819.
//!
//!  \type         	local
//!
//!  \param[in]     void
//!
//!  \return       	void
//!
//!******************************************************************************
Max14819::~Max14819() {

}

//!******************************************************************************
//!  function :    	reset
//!******************************************************************************
//! \brief        	reset the whole max14819 chip
//!
//!  \type         	local
//!
//!  \param[in]	  	void
//!
//!  \return        0 if successful
//!
//!******************************************************************************
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

//!******************************************************************************
//!  function :    	wakeUpRequest
//!******************************************************************************
//! \brief        	Generates wakeup impuls and handles communication speed
//!
//!  \type         	local
//!
//!  \param[in]     port            PORTA or PORTB
//!
//!  \return        communication speed. 1 if Error
//!
//!******************************************************************************
// TODO wakeUpRequest

//!******************************************************************************
//!  function :    	readRegister
//!******************************************************************************
//! \brief         	read register from max14819
//!
//!  \type       	local
//!
//!  \param[in]     reg             registeraddress to read
//!
//!  \return        registervalue
//!
//!******************************************************************************
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

//!******************************************************************************
//!  function :    	writeRegister
//!******************************************************************************
//!  \brief        	write register from max14819
//!
//!  \type        	local
//!
//!  \param[in]     reg             register address
//!  \param[in]     data            byte to write
//!
//!  \return        0 if successful
//!
//!******************************************************************************
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

//!******************************************************************************
//!  function :    	writeData
//!******************************************************************************
//!  \brief        	send data to device
//!
//!  \type        	local
//!
//!  \param[in]     mc                  master command
//!  \param[in]     sizeData            size in Byte of data
//!  \param[in]     *pData              pointer to data
//!  \param[in]     sizeAnswer          size in byte of answer
//!  \param[in]     mSeqType           M-seqence type
//!  \param[in]     port                port to send data
//!
//!  \return        0 if success
//!
//!******************************************************************************
// TODO writeData

//!******************************************************************************
//!  function :    	writeData
//!******************************************************************************
//!  \brief       	send data to device
//!
//!  \type        	local
//!
//!  \param[in]     uint8_t mc			master command
//!  \param[in]     sizeData	        size in Byte of data
//!  \param[in]     *pData		        pointer to data
//!  \param[in]     sizeAnswer	        size in byte of answer
//!  \param[in]     mSeqType	        M-seqence type
//!  \param[in]     port		        port to send data
//!
//!  \return        0 if success
//!
//!******************************************************************************
// TODO writeData

//!******************************************************************************
//!  function :    	readData
//!******************************************************************************
//!  \brief        	readMessage from device
//!
//!  \type         	local
//!
//!  \param[in]     *pData              pointer to data
//!  \param[in]     sizeData            size of data
//!  \param[in]     port                driver PORTA or PORTB
//!
//!  \return       	0 if success
//!
//!******************************************************************************
// TODO readData

//!******************************************************************************
//!  function :    	enableCyclicSend
//!******************************************************************************
//!  \brief         Set master command, which will be send periodically.
//!                 Set cycleTime to 0 to use the minCycleTime from the device.
//!
//!  \type          local
//!
//!  \param[in]     mc                  master command, only one message possible
//!  \param[in]     sizeData            size in byte of data
//!  \param[in]     *pData              pointer to data
//!  \param[in]     sizeAnswer          size in byte of answer
//!  \param[in]     mSeqType            M-seqence type
//!  \param[in]     minCycleTime        in a multiple of 0.1ms, min 0.4ms, max 132.8ms
//!  \param[in]     port                port to send data
//!
//!  \return        0 if success
//!
//!******************************************************************************
// TODO enableCyclicSend

//!******************************************************************************
//!  function :    	disableCyclicSend
//!******************************************************************************
//! \brief          Disable cyclic send and set the cyclic send timer to
//!                 minCycleTime
//!
//!  \type          local
//!
//!  \param[in]     port                PORTA or PORTB
//!
//!  \return        0 if success
//!
//!******************************************************************************
// TODO disableCyclicSend

//!******************************************************************************
//!  function :    	enableLedControl
//!******************************************************************************
//! \brief          Enables to controll the two leds portXLedRxRdy, portXLedRxErr
//!                 with SPI. Interrupts on these pins are disabled.
//!
//!  \type          local
//!
//!  \param[in]     port	            PORTA or PORTB
//!
//!  \return        0 if success
//!
//!******************************************************************************
// TODO enableLedControl

//!******************************************************************************
//!  function :    	disableLedControl
//!******************************************************************************
//!  \brief        	Disables the controll of the two leds portXLedRxRdy,
//!					portXLedRxErr with SPI. Interrupts on these pins are enabled.
//!
//!  \type         	local
//!
//!  \param[in]	  	port                PORTA or PORTB
//!
//!  \return       	0 if success
//!
//!******************************************************************************
// TODO disableLedControl

//!******************************************************************************
//!  function :    	writeLed
//!******************************************************************************
//!  \brief         Write Leds from MAX14819 via SPI.
//!
//!  \type          local
//!
//!  \param[in]     led
//!  \param[in]     state       LED_ON (1) or LED_OFF (0)
//!
//!  \return        0 if success
//!
//!******************************************************************************
// TODO writeLED

//!******************************************************************************
//!  function :    	writeDIConfig
//!******************************************************************************
//!  \brief         Initialize the DI input
//!
//!  \param[in]     port            PORTA or PORTB
//!  \param[in]     currentType     CURRENT_SOURCE or CURRENT_SINK or CURRENT_DISABLE
//!  \param[in]     threshold       THRSLD_TYPE1 or THRSLD_TYPE2
//!  \param[in]     filter          FILTER_EN or FILTER_DIS
//!
//!  \return        0 if success
//!
//!******************************************************************************
// TODO writeDIConfig

//!******************************************************************************
//!  function :     readDIConfig
//!******************************************************************************
//!  \brief         Read the configuration of the DI current control
//!
//!  \param[in]     port            PORTA or PORTB
//!
//!  \return        current source / sink or disabled
//!
//!******************************************************************************
// TODO readDIConfig

//!******************************************************************************
//!  function :    	readCQ
//!******************************************************************************
//! \brief          Read the level of the CQ line
//!
//!  \param[in]     port        PORTA or PORTB
//!
//!  \return        HIGH or LOW
//!
//!******************************************************************************
// TODO readCQ

//!******************************************************************************
//!  function :     writeCQ
//!******************************************************************************
//!  \brief         Drive the CQ to 0 V or 24 V
//!
//!  \param[in]     port            PORTA or PORTB
//!  \param[in]     value           HIGH or LOW
//!
//!  \return        0 if success
//!
//!******************************************************************************
// TODO writeCQ

//!******************************************************************************
//!  function :    	readDI
//!******************************************************************************
//! \brief        	Read the level of the DI line
//!
//!  \param[in]	  	port        PORTA or PORTB
//!
//!  \return       	HIGH or LOW
//!
//!******************************************************************************
// TODO writeDI

Max14819::Max14819_Port::Max14819_Port()
{
    // TODO init of Port
}

Max14819::Max14819_Port::~Max14819_Port()
{
    // TODO deinit of Port
}

void Max14819::Max14819_Port::setMode(Mode mode)
{
    // TODO set mode
}


//!******************************************************************************
//!  function :    	calculate_CKT
//!******************************************************************************
//!  \brief         calculate the checksum byte for master, for more informations
//!                 see IO-Link Specifications, A1.6, S.195
//!
//!  \type          local
//!
//!  \param[in]	    uint8_t mc          mastercommand data
//!  \param[in]     *data       pointer to transmit data
//!  \param[in]     dataSize    number of bytes transmit data
//!  \param[in]     type        m-seqeunce type depending on sensor
//!
//!  \return        uint8_t CKT         checksum
//!
//!******************************************************************************
// TODO move to IOLink Library
uint8_t calculateCKT(uint8_t mc, uint8_t *data, uint8_t dataSize, uint8_t type) {
    // Insert m-sequence type (bit6, 7)
    uint8_t CKT = uint8_t(type << 6);

    // XOR all Bytes (including MC, CKT, PD and OD)
    uint8_t CKT_XOR = mc ^ 0x52; // Seed value 0x52
    CKT_XOR ^= CKT;
    for (uint8_t i = 0; i < dataSize; i++) {
        CKT_XOR ^= data[i];
    }

    // calculate bits 5-0
    CKT |= uint8_t((((CKT_XOR >> 7) ^ (CKT_XOR >> 5) ^ (CKT_XOR >> 3) ^ (CKT_XOR >> 1))  & 0x01) << 5);
    CKT |= uint8_t((((CKT_XOR >> 6) ^ (CKT_XOR >> 4) ^ (CKT_XOR >> 2) ^ (CKT_XOR >> 0)) & 0x01) << 4);
    CKT |= uint8_t((((CKT_XOR >> 7) ^ ((CKT_XOR >> 6))) & 0x01) << 3);
    CKT |= uint8_t((((CKT_XOR >> 5) ^ ((CKT_XOR >> 4))) & 0x01) << 2);
    CKT |= uint8_t((((CKT_XOR >> 3) ^ ((CKT_XOR >> 2))) & 0x01) << 1);
    CKT |= uint8_t((((CKT_XOR >> 1) ^ ((CKT_XOR >> 0))) & 0x01) << 0);

    return CKT;
}
