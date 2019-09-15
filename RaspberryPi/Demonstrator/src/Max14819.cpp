
//!*****************************************************************************
//!  \file        Max14819.cpp
//!*****************************************************************************
//!
//!  \brief		 max14819 driver specific layer
//!
//!  \author     Pascal Frei (freip2)
//!
//! \date       27.06.2019
//!
//! \remark     Last Modification
//!				 \li freip2, 27.06.2019, Cleaned
//!              \li freip2, 14.05.2019, Created
//!
//!*****************************************************************************
//!	Copyright (C) 2019, Pascal Frei
//!
//!	This program is free software: you can redistribute it and/or modify
//!	it under the terms of the GNU General Public License as published by
//!	the Free Software Foundation, either version 3 of the License, or
//!	any later version.
//!
//!	but WITHOUT ANY WARRANTY; without even the implied warranty of
//!	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//!	GNU General Public License for more details.
//!
//!	You should have received a copy of the GNU General Public License
//!	along with this program.  If not, see <http://www.gnu.org/licenses/>.
//!
//!******************************************************************************

//!**** Header-Files ************************************************************
#include <stdint.h>
#include <stdio.h>
//#include "Arduino.h"
//#include <SPI.h>

#include "../include/IOLMasterPort.h"
#include "../include/Max14819.h"

//!**** Macros ******************************************************************
constexpr uint8_t read = 0b00000001;
constexpr uint8_t write = 0b01111111;

#define LOW 0
#define HIGH 1

//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************
uint8_t calculateCKT(uint8_t mc, uint8_t *data, uint8_t dataSize, uint8_t type);

//!**** Data ********************************************************************

//!**** Implementation **********************************************************
using namespace max14819;

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
Max14819::Max14819(){
	driver_ = DRIVER01;
	isInitPortA_ = 0;
	isInitPortB_ = 0;
	isLedCtrlPortAEn_ = 0;
	isLedCtrlPortBEn_ = 0;
	comSpeedRegA = 0;
	comSpeedRegB = 0;
	Hardware = nullptr;
}

//!******************************************************************************
//!  function :    	max14819() constructor
//!******************************************************************************
//!  \brief        	Initialize the communication interface for the max14819.
//!
//!  \type         	local
//!
//!  \param[in]     driver          DRIVER01 or DRIVER23
//!
//!  \return        void
//!
//!******************************************************************************
Max14819::Max14819(DriverSelect driver, HardwareRaspberry * hardware){
	driver_ = driver;
	isInitPortA_ = 0;
	isInitPortB_ = 0;
	isLedCtrlPortAEn_ = 0;
	isLedCtrlPortBEn_ = 0;
	comSpeedRegA = 0;
	comSpeedRegB = 0;
	Hardware = hardware;

}
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
//!  function :    	begin
//!******************************************************************************
//!* \brief        	Initialize the communication interface for the max14819 and
//!					set the default configuration of the max14819. Enables the
//!					L+ mosfet to power the device. Remember that driver01 must
//! 				be initilized to use driver23 because the daisychaining of
//!					the clock.
//!  \type         	local
//!
//!  \param[in]     port                PORTA or PORTB
//!
//!  \return        0 if success
//!
//!******************************************************************************
uint8_t Max14819::begin(PortSelect port) {
    uint8_t retValue = SUCCESS;
    uint8_t shadowReg = 0;

    switch (driver_) {
    case DRIVER01:
        // Initialize IOs and clock for driver 01
        // only initialize IOs and clock once for both
        if ((isInitPortA_ == 0) && (isInitPortB_ == 0)) {
            // Initialize IOs
            Hardware->IO_PinMode(port01CS, Hardware->out);
			Hardware->IO_PinMode(port01IRQ, Hardware->in_pullup);
            Hardware->IO_PinMode(port0DI, Hardware->in_pullup);
            Hardware->IO_PinMode(port1DI, Hardware->in_pullup);
            Hardware->IO_PinMode(port0LedGreen, Hardware->out);
            Hardware->IO_PinMode(port0LedRed, Hardware->out);
            Hardware->IO_PinMode(port0RxError, Hardware->in_pullup);
            Hardware->IO_PinMode(port0RxReady, Hardware->in_pullup);
            Hardware->IO_PinMode(port1LedGreen, Hardware->out);
            Hardware->IO_PinMode(port1LedRed, Hardware->out);
            Hardware->IO_PinMode(port1RxError, Hardware->in_pullup);
            Hardware->IO_PinMode(port1RxReady, Hardware->in_pullup);

            // Define all SPI signals for the Geckoboard as inputs. if not, MOSI cant be thrown to 0V
            /*Hardware->IO_PinMode(50, Hardware->in);
            Hardware->IO_PinMode(52, Hardware->in);
            Hardware->IO_PinMode(53, Hardware->in);*/

            // Enable extern crystal
            retValue = uint8_t(retValue | writeRegister(Clock, TXTXENDis | ClkOEn | XtalEn)); // Frequency is 14.745 MHz

            switch (port) {
            case PORTA:
                // Set outputs high for Port A (low-active)
                Hardware->IO_Write(port0LedGreen, HIGH);
                Hardware->IO_Write(port0LedRed, HIGH);

                // Initialize LEDs for other port if not allready initialized
                if (isInitPortB_ == 0) {
                    Hardware->IO_Write(port1LedGreen, HIGH);
                    Hardware->IO_Write(port1LedRed, HIGH);
                }

                // Port A successfully initialized
                isInitPortA_ = 1;
                break;
            case PORTB:
                // Set outputs high for Port B (low-active)
                Hardware->IO_Write(port1LedGreen, HIGH);
                Hardware->IO_Write(port1LedRed, HIGH);

                // Initialize LEDs for other port if not allready initialized
                if (isInitPortA_ == 0) {
                    Hardware->IO_Write(port0LedGreen, HIGH);
                    Hardware->IO_Write(port0LedRed, HIGH);
                }

                // Port B successfully initialized
                isInitPortB_ = 1;
                break;
            default:
                retValue = ERROR;
                break;
            } // switch(port
        } // switch

        break;
    case DRIVER23:
        // Initialize IOs and clock for driver 23
        // only initialize IOs and clock once for both ports
        if ((isInitPortA_ == 0) && (isInitPortB_ == 0)) {
            // Initialize IOs
            Hardware->IO_PinMode(port23CS, Hardware->out);
            Hardware->IO_PinMode(port23IRQ, Hardware->in_pullup);
            Hardware->IO_PinMode(port2DI, Hardware->in_pullup);
            Hardware->IO_PinMode(port3DI, Hardware->in_pullup);
            Hardware->IO_PinMode(port2LedGreen, Hardware->out);
            Hardware->IO_PinMode(port2LedRed, Hardware->out);
            Hardware->IO_PinMode(port2RxError, Hardware->in_pullup);
            Hardware->IO_PinMode(port2RxReady, Hardware->in_pullup);
            Hardware->IO_PinMode(port3LedGreen, Hardware->out);
            Hardware->IO_PinMode(port3LedRed, Hardware->out);
            Hardware->IO_PinMode(port3RxError, Hardware->in_pullup);
            Hardware->IO_PinMode(port3RxReady, Hardware->in_pullup);

            // Set chipselect output high (low-active)
            Hardware->IO_Write(port23CS, HIGH);

            // Enable clocking from another max14819
            retValue = uint8_t(retValue | writeRegister(Clock, TXTXENDis | ExtClkEn | ClkDiv0 | ClkDiv1)); // external OSC enable, 3.686 MHz input frequency
        }
        switch (port) {
        case PORTA:
            // Set outputs high for Port A (low-active)
            Hardware->IO_Write(port2LedGreen, HIGH);
            Hardware->IO_Write(port2LedRed, HIGH);

            // Initialize LEDs for other port if not allready initialized
            if (isInitPortA_ == 0) {
                Hardware->IO_Write(port3LedGreen, HIGH);
                Hardware->IO_Write(port3LedRed, HIGH);
            }

            // Port A successfully initialized
            isInitPortA_ = 1;

            break;
        case PORTB:
            // Set outputs high for Port B (low-active)
            Hardware->IO_Write(port3LedGreen, HIGH);
            Hardware->IO_Write(port3LedRed, HIGH);

            // Initialize LEDs for other port if not allready initialized
            if (isInitPortB_ == 0) {
                Hardware->IO_Write(port2LedGreen, HIGH);
                Hardware->IO_Write(port2LedRed, HIGH);
            }
            // Port B successfully initialized
            isInitPortB_ = 1;
            break;
        default:
            retValue = ERROR;
            break;
        } // switch(port)

        break;
    default:
        retValue = ERROR;
        break;
    } // switch(driver)

    // Reset max14819 register
    retValue = uint8_t(retValue | reset(port));

    // Wait 1 s for turning on the powersupply for sensor
	Hardware->wait_for(INIT_POWER_OFF_DELAY);

    // Initialize global registers
    retValue = uint8_t(retValue | writeRegister(DrvrCurrLim, CL1 | CL0 | CLBL1 | CLBL0 | ArEn)); //CQ 500 mA currentlimit, 5 ms min error duration before interrupt

    // Initialize the port sepcific registers
    switch (port) {
    case PORTA:
        // Set all Interrupts
        shadowReg = readRegister(InterruptEn);
        retValue = uint8_t(retValue | writeRegister(InterruptEn, StatusIntEn | WURQIntEn | TxErrIntEnA | RxErrIntEnA | RxDaRdyIntEnA | shadowReg));
        // Enable RxReady and RyError LED
        shadowReg = readRegister(LEDCtrl);
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, RxRdyEnA | RxErrEnA | shadowReg));
        // Initialize the Channel A register
        retValue = uint8_t(retValue | writeRegister(LCnfgA, LRT0 | LBL0 | LBL1 | LClimDis | LEn)); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        retValue = uint8_t(retValue | writeRegister(CQCfgA, SinkSel0 | PushPul)); // Int Current Sink, 5 mA, PushPull, Channel Enable
        break;
    case PORTB:
        // Set all Interrupts
        shadowReg = readRegister(InterruptEn);
        retValue = uint8_t(retValue | writeRegister(InterruptEn, StatusIntEn | WURQIntEn | TxErrIntEnB | RxErrIntEnB | RxDaRdyIntEnB | shadowReg));
        // Enable RxReady and RyError LED
        shadowReg = readRegister(LEDCtrl);
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, RxRdyEnB | RxErrEnB | shadowReg));
        // Initialize the Channel A register
        retValue = uint8_t(retValue | writeRegister(LCnfgB, LRT0 | LBL0 | LBL1 | LClimDis | LEn)); // Enable current retry 0.4s,  disable currentlimiting, enable Current
        retValue = uint8_t(retValue | writeRegister(CQCfgB, SinkSel0 | PushPul)); // Int Current Sink, 5 mA, PushPull, Channel Enable
        break;
    default:
        retValue = ERROR;
        break;
    } // switch(port)

    // Wait 0.2s for bootup of the device
	Hardware->wait_for(INIT_BOOTUP_DELAY);

    // Return Error state
    return retValue;
}

//!******************************************************************************
//!  function :    	end
//!******************************************************************************
//! \brief        	Deinitialize the communication interface for the max14819.
//!
//!  \type         	local
//!
//!  \param[in]     port            PORTA or PORTB
//!
//!  \return        0 if success
//!
//!******************************************************************************
uint8_t Max14819::end(PortSelect port) {
    uint8_t retValue = SUCCESS;

    // Reset max14819 registers
    retValue = reset(port);

    // turn off all LEDs
    switch(port) {
        case PORTA:
            Hardware->IO_Write(port1LedGreen, HIGH);
            Hardware->IO_Write(port1LedRed, HIGH);
            break;
        case PORTB:
            Hardware->IO_Write(port0LedGreen, HIGH);
            Hardware->IO_Write(port0LedRed, HIGH);
            break;
        default:
        retValue = ERROR;
        break;
    } // switch(port)

    // Return Error state
    return retValue;
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
//!  function :    	reset
//!******************************************************************************
//! \brief        	Reset port A or B of max14819 chip
//!
//!  \type         	local
//!
//!  \param[in]     port	PORTA or PORTB
//!
//!  \return       	uint8_t			0 if successful
//!
//!******************************************************************************
uint8_t Max14819::reset(PortSelect port) {
    uint8_t retValue = SUCCESS;

// Reset all max14819 registers only for selected port
    if (port == PORTA) {
// Reset all port A register
        retValue = uint8_t(retValue | writeRegister(ChanStatA, Rst));
// Reset trigger register
        retValue = uint8_t(retValue | writeRegister(Trigger, 0));
// Reset DrvrCurrentLimit register
        retValue = uint8_t(retValue | writeRegister(DrvrCurrLim, 0));
// Disable Interrupts only for port A
        uint8_t shadowReg = readRegister(InterruptEn);
        retValue = uint8_t(retValue | writeRegister(InterruptEn, uint8_t(shadowReg & ~(TxErrIntEnA | RxErrIntEnA | RxDaRdyIntEnA))));
// Disable LEDs only for port A
        shadowReg = readRegister(LEDCtrl);
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, uint8_t(shadowReg & ~(LEDEn2A | RxErrEnA | LEDEn1A | RxRdyEnA))));
    }
// Reset all max14819 registers only for selected port
    if (port == PORTB) {
// Reset all port B register
        retValue = uint8_t(retValue | writeRegister(ChanStatB, Rst));
// Reset trigger register
        retValue = uint8_t(retValue | writeRegister(Trigger, 0));
// Reset DrvrCurrentLimit register
        retValue = uint8_t(retValue | writeRegister(DrvrCurrLim, 0));
// Disable Interrupts only for port B
        uint8_t shadowReg = readRegister(InterruptEn);
        retValue = uint8_t(retValue | writeRegister(InterruptEn, uint8_t(shadowReg & ~(TxErrIntEnB | RxErrIntEnB | RxDaRdyIntEnB))));
// Disable LEDs only for port A
        shadowReg = readRegister(LEDCtrl);
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, uint8_t(shadowReg & ~(LEDEn2B | RxErrEnB | LEDEn1B | RxRdyEnB))));
    }
// Return Error state
    return retValue;
}
//!******************************************************************************
//!  function :    	readStatus
//!******************************************************************************
//! \brief        	Init peripheries and starts the tasks.
//!
//!  \type         	local
//!
//!  \param[in]     port
//!
//!  \return        0 if success
//!
//!******************************************************************************
uint8_t Max14819::readStatus(PortSelect port) {
    return 0;
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
uint8_t Max14819::wakeUpRequest(PortSelect port, uint32_t * comSpeed_ret) {
    uint32_t comSpeed;
    uint8_t retValue = 0;
    uint8_t comReqRunning = 0;
    uint8_t timeOutCounter = 0;
    uint16_t length = 0;

    // wake up and communication establishing for selected port
    switch(port){
    case PORTA:
        // Start wakeup and communcation
        retValue = uint8_t(retValue | writeRegister(IOStCfgA, 0)); // Disable tx needed for wake up
        retValue = uint8_t(retValue | writeRegister(ChanStatA, FramerEn)); // Enable ChanA Framer
        retValue = uint8_t(retValue | writeRegister(MsgCtrlA, 0)); // Dont use InsChks when transmit OD Data, max14819 doesnt calculate it right
        retValue = uint8_t(retValue | writeRegister(CQCtrlA, EstCom));     // Start communication

        // Wait till establish communication sequence is over or timeout is reached
        do {
            comReqRunning = readRegister(CQCtrlA);
            comReqRunning &= EstCom;
            timeOutCounter++;
            Hardware->wait_for(1);
        } while (comReqRunning || (timeOutCounter < INIT_WURQ_TIMEOUT));

		Hardware->wait_for(10);
        // Clear buffer
        length = readRegister(RxFIFOLvlA);
        for (uint8_t i = 0; i < length; i++) {
            readRegister(TxRxDataA);
        }

        // read communication speed
        comSpeedRegA = readRegister(CQCtrlA) & (ComRt0 | ComRt1);
        comSpeed = comSpeedRegA;
        if (comSpeed == 0) {
            return ERROR;
        }
        break;
    case PORTB:
        // Start wakeup and communcation
        retValue = uint8_t(retValue | writeRegister(IOStCfgB, 0)); // Disable tx needed for wake up
        retValue = uint8_t(retValue | writeRegister(ChanStatB, FramerEn)); // Enable Chanb Framer
        retValue = uint8_t(retValue | writeRegister(MsgCtrlB, 0)); // Dont use InsChks when transmit OD Data, max14819 doesnt calculate it right
        retValue = uint8_t(retValue | writeRegister(CQCtrlB, EstCom));     // Start communication

        // Wait till establish communication sequence is over or timeout is reached
        do {
            comReqRunning = readRegister(CQCtrlB);
            comReqRunning &= EstCom;
            timeOutCounter++;
			Hardware->wait_for(1);
        } while (comReqRunning || (timeOutCounter < INIT_WURQ_TIMEOUT));

		Hardware->wait_for(10);
        // Clear buffer
       length = readRegister(RxFIFOLvlB);
        for (uint8_t i = 0; i < length; i++) {
            readRegister(TxRxDataB);
        }

        // read communication speed
        comSpeedRegB = readRegister(CQCtrlB) & (ComRt0 | ComRt1);
        comSpeed = comSpeedRegB;
        if (comSpeed == 0) {
            return ERROR;
        }
        break;
    default:
        retValue = ERROR;
        break;
    } // switch(port)

    // Set correct communication speed in kBaud/s
    switch (comSpeed) {
    case 0:
        // No communication established
        *comSpeed_ret = 0;
        printf("WAKEUP-Error\n");// TODO: 
        break;
    case ComRt0:
        // Communication established at 4.8 kBaud/s
        *comSpeed_ret = 4800;
        printf("WAKEUP-4800\n");// TODO: 
        break;
    case ComRt1:
        // Communication established at 38.4 kBaud/s
        *comSpeed_ret = 38400;
        printf("WAKEUP-38400\n");// TODO: 
        break;
    case (ComRt0 | ComRt1):
        // Communication established at 230.4 kBaud/s
        *comSpeed_ret = 230400;
        printf("WAKEUP-230400\n");// TODO: 
        break;
    default:
		return ERROR;
        break;
    }
    return SUCCESS;
}

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
        Hardware->Serial_Write("Registeraddress out of range");
        return ERROR;
    }

    switch(driver_){
    case DRIVER01:
        // Mask read register with the read cmd and set spi address of the max14819
        reg = reg | (read << 7) | (port01Address << 5);
        // Set channel to 0
        channel = 0;
        break;
    case DRIVER23:
        // Mask read register with the read cmd and set spiad dress of the max14819
        reg = reg | (read << 7) | (port23Address << 5);
        // Set channel to 1
        channel = 1;
        break;
    default:
        break;
    } // switch(driver)

    // Predefine buffer
    buf[0] = reg;
    buf[1] = 0x00;

    // Send the device the register you want to read:
    Hardware->SPI_Write(channel, buf, 2);

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
    uint8_t channel = 0;

    // Check if register address is in the correct range
    if (reg > MAX_REG) {
        Hardware->Serial_Write("Registeraddress out of range");
        return ERROR;
    }
    // Set write bit in register command
    reg &= write;

    switch (driver_) {
    case DRIVER01:
        // Set SPI address of the max14819
        reg |= (port01Address << 5);
        // Set channel to 0
        channel = 0;
        break;
    case DRIVER23:
        // Set SPI address of the max14819
        reg |= (port23Address << 5);
        // Set channel to 1
        channel = 1;
        break;
    default:
        retValue = ERROR;
        break;
    }

    // Send SPI telegram
    buf[0] = reg;
    buf[1] = data;
    Hardware->SPI_Write(channel, buf, 2);

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
uint8_t Max14819::writeData(uint8_t mc, uint8_t data, uint8_t sizeAnswer, uint8_t mSeqType, PortSelect port) {
    uint8_t retValue = SUCCESS;

    uint8_t bufferRegister;
    // Use corresponding transmit FIFO address
    switch(port){
      case PORTA:
          bufferRegister = TxRxDataA;
          break;
      case PORTB:
          bufferRegister = TxRxDataB;
          break;
      default:
          bufferRegister = 0;
          retValue = ERROR;
          break;
      } // switch(port)

    // Write message to max14819 FIFO
    retValue = uint8_t(retValue | writeRegister(bufferRegister, sizeAnswer)); // number of bytes for answer
    retValue = uint8_t(retValue | writeRegister(bufferRegister, 3)); // 3 bytes to send including master command and checksum
    retValue = uint8_t(retValue | writeRegister(bufferRegister, mc)); // begin of message, master command
    retValue = uint8_t(retValue | writeRegister(bufferRegister, calculateCKT(mc, &data, 1, mSeqType))); // second byte of message, checksum (CKT)
    retValue = uint8_t(retValue | writeRegister(bufferRegister, data)); // send data to buffer, increment address of data after every byte

    // Enable transmit message
    switch(port){
    case PORTA:
        retValue = uint8_t(retValue | writeRegister(CQCtrlA, CQSend | comSpeedRegA));
        break;
    case PORTB:
        retValue = uint8_t(retValue | writeRegister(CQCtrlB, CQSend | comSpeedRegB));
        break;
    default:
        retValue = ERROR;
        break;
    } // switch(port)

    // Return Error state
    return retValue;
}
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
uint8_t Max14819::writeData(uint8_t mc, uint8_t sizeData, uint8_t *pData, uint8_t sizeAnswer, uint8_t mSeqType, PortSelect port) {
    uint8_t retValue = SUCCESS;

    // Test if message is not too long
    if ((sizeData + 2) > MAX_MSG_LENGTH) { //include 1 byte masterc ommand and 1 byte for checksum
        return ERROR;
    }

    uint8_t bufferRegister;
    // Use corresponding transmit FIFO address
    switch(port){
    case PORTA:
        bufferRegister = TxRxDataA;
        break;
    case PORTB:
        bufferRegister = TxRxDataB;
        break;
    default:
        bufferRegister = 0;
        retValue = ERROR;
        break;
    } // switch(port)

    // Write message to max14819 FIFO
    retValue = uint8_t(retValue | writeRegister(bufferRegister, sizeAnswer)); // number of bytes for answer
    retValue = uint8_t(retValue | writeRegister(bufferRegister, uint8_t(sizeData + 2))); // number of bytes to send including master command and checksum
    retValue = uint8_t(retValue | writeRegister(bufferRegister, mc)); // begin of message, master command
    retValue = uint8_t(retValue | writeRegister(bufferRegister, calculateCKT(mc, pData, sizeData, mSeqType))); // second byte of message, checksum (CKT)
    for (uint8_t i = 0; i < sizeData; i++) {
        retValue = uint8_t(retValue | writeRegister(bufferRegister, *pData)); // send data to buffer, increment address of data after every byte
        pData++;
    }
    // Enable transmit message
    switch(port){
    case PORTA:
       retValue = uint8_t(retValue | writeRegister(CQCtrlA, CQSend | comSpeedRegA));
       break;
    case PORTB:
       retValue = uint8_t(retValue | writeRegister(CQCtrlB, CQSend | comSpeedRegB));
       break;
    default:
       retValue = ERROR;
    break;
   } // switch(port)
    // Return Error state
    return retValue;

}
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
uint8_t Max14819::readData(uint8_t *pData, uint8_t sizeData, PortSelect port) {
    uint8_t bufferRegister;
    uint8_t retValue = SUCCESS;
    // Use corresponding transmit FIFO address
    switch(port){
    case PORTA:
        bufferRegister = TxRxDataA;
        break;
    case PORTB:
        bufferRegister = TxRxDataB;
            break;
    default:
        retValue = ERROR;
        bufferRegister = 0;
        break;
    } // switch(port)

    // Controll if the aswer has the expected length (first byte in the FIFO is the messagelength)
    if (sizeData != readRegister(bufferRegister)) {
        // TODO Error Handling if Buffer is corrupted
        retValue = ERROR;
    }

    // Read data from FIFO
    for (uint8_t i = 0; i < sizeData; i++) {
        *pData++ = readRegister(bufferRegister);
    }
    // Return Error state
    return retValue;
}
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
uint8_t Max14819::enableCyclicSend(uint8_t mc, uint8_t sizeData, uint8_t *pData,uint8_t sizeAnswer, uint8_t mSeqType, uint16_t cycleTime,PortSelect port) {
    uint8_t retValue = SUCCESS;

    // Set cycleTime (use minCycleTime stored allready CyclTmrA/B when 0
    uint8_t cycleBase = 0;
    uint8_t cycleMult = 0;
    if (cycleTime == 0) {
    } else if ((cycleTime >= 4) && (cycleTime <= 63)) {
        // Calculate CyclTmr register values, base 0.1ms, no offset
        cycleBase = 1;
        cycleMult = uint8_t(cycleTime / cycleBase);
        // Write cycle base and cycle multiplicator in cycle register
        if (port == PORTA)
            retValue = uint8_t(retValue | writeRegister(CyclTmrA, cycleMult));
        if (port == PORTB)
            retValue = uint8_t(retValue | writeRegister(CyclTmrB, cycleMult));
    } else if (cycleTime <= 316) {
        // Calculate CyclTmr register values, base 0.4ms, offset 6.4ms
        cycleBase = 4;
        cycleMult = uint8_t((cycleTime - 64) / cycleBase);
        // Write cycle base and cycle multiplicator in cycle register
        if (port == PORTA)
            retValue = uint8_t(retValue | writeRegister(CyclTmrA, TCyclBs0 | cycleMult));
        if (port == PORTB)
            retValue = uint8_t(retValue | writeRegister(CyclTmrB, TCyclBs0 | cycleMult));
    } else if (cycleTime <= 1328) {
        // Calculate CyclTmr register values, base 1.6ms, offset 32ms
        cycleBase = 16;
        cycleMult = uint8_t((cycleTime - 320) / cycleBase);
        // Write cycle base and cycle multiplicator in cycle register
        if (port == PORTA)
            retValue = uint8_t(retValue | writeRegister(CyclTmrA, TCyclBs1 | cycleMult));
        if (port == PORTB)
            retValue = uint8_t(retValue | writeRegister(CyclTmrB, TCyclBs1 | cycleMult));
    } else {
        return ERROR;
    }

    // Test if message is not too long
    if ((sizeData + 2) > MAX_MSG_LENGTH) { //include 1 byte masterc ommand and 1 byte for checksum
        return ERROR;
    }

    uint8_t bufferRegister;
    // Use corresponding transmit FIFO address
    if (port == PORTA)
        bufferRegister = TxRxDataA;
    if (port == PORTB)
        bufferRegister = TxRxDataB;

    // Write message to max14819 FIFO
    retValue = uint8_t(retValue | writeRegister(bufferRegister, sizeAnswer)); // number of bytes for answer
    retValue = uint8_t(retValue | writeRegister(bufferRegister, uint8_t(sizeData + 2))); // number of bytes to send including master command and checksum
    retValue = uint8_t(retValue | writeRegister(bufferRegister, mc)); // begin of message, master command
    retValue = uint8_t(retValue | writeRegister(bufferRegister, calculateCKT(mc, pData, sizeData, mSeqType))); // second byte of message, checksum (CKT)
    for (uint8_t i = 0; i < sizeData; i++) {
        retValue = uint8_t(retValue | writeRegister(bufferRegister, *pData)); // send data to buffer, increment address of data after every byte
        pData++;
    }

    // enable cyclic send
    if (port == PORTA)
        retValue = uint8_t(retValue | writeRegister(CQCtrlA, CycleTmrEn | comSpeedRegA));
    if (port == PORTB)
        retValue = uint8_t(retValue | writeRegister(CQCtrlB, CycleTmrEn | comSpeedRegB));

    // Return Error state
    return retValue;
}
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
uint8_t Max14819::disableCyclicSend(PortSelect port) {
    uint8_t retValue = SUCCESS;

    // Disable cyclic send
    if (port == PORTA)
        retValue = uint8_t(retValue | writeRegister(CQCtrlA, comSpeedRegA));
    if (port == PORTB)
        retValue = uint8_t(retValue | writeRegister(CQCtrlB, comSpeedRegB));

    // Reset CyclTmr register to minCycleTime
    uint16_t cycleTime = 100; // TODO use minCycleTime stored in port Object
    uint8_t cycleBase = 0;
    uint8_t cycleMult = 0;
    if ((cycleTime >= 4) && (cycleTime <= 63)) {
        // Calculate CyclTmr register values, base 0.1ms, no offset
        cycleBase = 1;
        cycleMult = uint8_t(cycleTime / cycleBase);
        // Write cycle base and cycle multiplicator in cycle register
        if (port == PORTA)
            retValue = uint8_t(retValue | writeRegister(CyclTmrA, cycleMult));
        if (port == PORTB)
            retValue = uint8_t(retValue | writeRegister(CyclTmrB, cycleMult));
    } else if (cycleTime <= 316) {
        // Calculate CyclTmr register values, base 0.4ms, offset 6.4ms
        cycleBase = 4;
        cycleMult = uint8_t((cycleTime - 64) / cycleBase);
        // Write cycle base and cycle multiplicator in cycle register
        if (port == PORTA)
            retValue = uint8_t(retValue | writeRegister(CyclTmrA, TCyclBs0 | cycleMult));
        if (port == PORTB)
            retValue = uint8_t(retValue | writeRegister(CyclTmrB, TCyclBs0 | cycleMult));
    } else if (cycleTime <= 1328) {
        // Calculate CyclTmr register values, base 1.6ms, offset 32ms
        cycleBase = 16;
        cycleMult = uint8_t((cycleTime - 320) / cycleBase);
        // Write cycle base and cycle multiplicator in cycle register
        if (port == PORTA)
            retValue = uint8_t(retValue | writeRegister(CyclTmrA, TCyclBs1 | cycleMult));
        if (port == PORTB)
            retValue = uint8_t(retValue | writeRegister(CyclTmrB, TCyclBs1 | cycleMult));
    }
    // Return Error state
    return retValue;
}
//!******************************************************************************
//!  function :    	enableLedControl
//!******************************************************************************
//! \brief          Enables to controll the two leds portXRxReady, portXRxError
//!                 with SPI. Interrupts on these pins are disabled.
//!
//!  \type          local
//!
//!  \param[in]     port	            PORTA or PORTB
//!
//!  \return        0 if success
//!
//!******************************************************************************
uint8_t Max14819::enableLedControl(PortSelect port) {
    uint8_t retValue = SUCCESS;

    // Enable RxReady and RxError LED, disable interrupts RxReady and RxError
    // LEDs are switched off
    uint8_t shadowReg = readRegister(LEDCtrl);
    switch(port){
    case PORTA:
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, (shadowReg & 0xF0)));
       // Set Led Controll variable true
       isLedCtrlPortAEn_ = 1;
        break;
    case PORTB:
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, (shadowReg & 0x0F)));
       // Set Led Controll variable true
       isLedCtrlPortBEn_ = 1;
        break;
    default:
        retValue = ERROR;
        break;
    }

    // Return Error state
    return retValue;
}
//!******************************************************************************
//!  function :    	disableLedControl
//!******************************************************************************
//!  \brief        	Disables the controll of the two leds portXRxReady,
//!					portXRxError with SPI. Interrupts on these pins are enabled.
//!
//!  \type         	local
//!
//!  \param[in]	  	port                PORTA or PORTB
//!
//!  \return       	0 if success
//!
//!******************************************************************************
uint8_t Max14819::disableLedControl(PortSelect port) {
    uint8_t retValue = SUCCESS;

    // Disable RxReady and RxError LED, enable interrupts RxReady and RxError
    uint8_t shadowReg = readRegister(LEDCtrl);
    switch(port){
    case PORTA:
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, (shadowReg & 0xF0) | RxRdyEnA | RxErrEnA));
       // Set Led Controll variable false
       isLedCtrlPortAEn_ = 0;
        break;
    case PORTB:
        retValue = uint8_t(retValue | writeRegister(LEDCtrl, (shadowReg & 0x0F) | RxRdyEnB | RxErrEnB));
        // Set Led Controll variable false
        isLedCtrlPortBEn_ = 0;
        break;
    default:
        retValue = ERROR;
        break;
    }

    // Return Error state
    return retValue;
}
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
uint8_t Max14819::writeLed(uint8_t led, uint8_t state) {
    uint8_t retValue = SUCCESS;
    uint8_t shadowReg = 0;

    if ((state != LED_ON) && (state != LED_OFF)) {
        return ERROR;
    }

    switch(driver_){
    case DRIVER01:
        switch (led) {
        case port0LedGreen:
			Hardware->IO_Write(led, state);
            break;
        case port0LedRed:
			Hardware->IO_Write(led, state);
            break;
        case port0LedRxErr:
            if (isLedCtrlPortAEn_) {
                // Switch LED on, set corresponding bit in LEDCtrl register
                if (state == LED_ON) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn2A | shadowReg));
                }
                // Switch LED on, erase corresponding bit in LEDCtrl register
                if (state == LED_OFF) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn2A ^ shadowReg));
                }
            } else
                retValue = ERROR;
            break;
        case port0LedRxRdy:
            if (isLedCtrlPortAEn_) {
                // Switch LED on, set corresponding bit in LEDCtrl register
                if (state == LED_ON) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn1A | shadowReg));
                }
                // Switch LED on, erase corresponding bit in LEDCtrl register
                if (state == LED_OFF) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn1A ^ shadowReg));
                }
            }
            break;
        case port1LedGreen:
			Hardware->IO_Write(led, state);
            break;
        case port1LedRed:
			Hardware->IO_Write(led, state);
            break;
        case port1LedRxErr:
            if (isLedCtrlPortBEn_) {
                // Switch LED on, set corresponding bit in LEDCtrl register
                if (state == LED_ON) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn2B | shadowReg));
                }
                // Switch LED on, erase corresponding bit in LEDCtrl register
                if (state == LED_OFF) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn2B ^ shadowReg));
                }
            } else
                retValue = ERROR;
            break;
        case port1LedRxRdy:
            if (isLedCtrlPortBEn_) {
                // Switch LED on, set corresponding bit in LEDCtrl register
                if (state == LED_ON) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn1B | shadowReg));
                }
                // Switch LED on, erase corresponding bit in LEDCtrl register
                if (state == LED_OFF) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn1B ^ shadowReg));
                }
            } else
                retValue = ERROR;
            break;
        }// end switch(led)
        break;
    case DRIVER23:
        switch (led) {
        case port2LedGreen:
			Hardware->IO_Write(led, state);
            break;
        case port2LedRed:
			Hardware->IO_Write(led, state);
            break;
        case port2LedRxErr:
            if (isLedCtrlPortAEn_) {
                // Switch LED on, set corresponding bit in LEDCtrl register
                if (state == LED_ON) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn2A | shadowReg));
                }
                // Switch LED on, erase corresponding bit in LEDCtrl register
                if (state == LED_OFF) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn2A ^ shadowReg));
                }
            } else
                retValue = ERROR;
            break;
        case port2LedRxRdy:
            if (isLedCtrlPortAEn_) {
                // Switch LED on, set corresponding bit in LEDCtrl register
                if (state == LED_ON) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn1A | shadowReg));
                }
                // Switch LED on, erase corresponding bit in LEDCtrl register
                if (state == LED_OFF) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn1A ^ shadowReg));
                }
            }
            break;
        case port3LedGreen:
			Hardware->IO_Write(led, state);
            break;
        case port3LedRed:
			Hardware->IO_Write(led, state);
            break;
        case port3LedRxErr:
            if (isLedCtrlPortBEn_) {
                // Switch LED on, set corresponding bit in LEDCtrl register
                if (state == LED_ON) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn2B | shadowReg));
                }
                // Switch LED on, erase corresponding bit in LEDCtrl register
                if (state == LED_OFF) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn2B ^ shadowReg));
                }
            } else
                retValue = ERROR;
            break;
        case port3LedRxRdy:
            if (isLedCtrlPortBEn_) {
                // Switch LED on, set corresponding bit in LEDCtrl register
                if (state == LED_ON) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn1B | shadowReg));
                }
                // Switch LED on, erase corresponding bit in LEDCtrl register
                if (state == LED_OFF) {
                    shadowReg = readRegister(LEDCtrl);
                    retValue = uint8_t(retValue | writeRegister(LEDCtrl, LEDEn1B ^ shadowReg));
                }
            } else
                retValue = ERROR;
            break;
        } // end switch(led)
        break;
    default:
        retValue = ERROR;
        break;
    } // end switch(driver)

    return retValue;
}
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
uint8_t Max14819::writeDIConfig(PortSelect port, uint8_t currentType,
        uint8_t threshold, uint8_t filter) {
    uint8_t retValue = SUCCESS;
    uint8_t shadowReg = 0;

    // Write config
    if (port == PORTA) {
        // Read back the actual state, does not change upper 4 bits
        shadowReg = (readRegister(IOStCfgA)) & 0xF0;
        retValue = uint8_t(retValue | writeRegister(IOStCfgA, (shadowReg | currentType | threshold | filter)));
    }
    if (port == PORTB) {
        // Read back the actual state, does not change upper 4 bits
        shadowReg = (readRegister(IOStCfgB)) & 0xF0;
        retValue = uint8_t(retValue | writeRegister(IOStCfgB, (shadowReg | currentType | threshold | filter)));
    }

    return retValue;
}
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
uint8_t Max14819::readDIConfig(PortSelect port) {
uint8_t config = 0;
    switch(port){
    case PORTA:
        // Return current mode (last 2 bits) from IOStCfgA register
        config = ((readRegister(IOStCfgA)) & 0x03);
        break;
    case PORTB:
        // Return current mode (last 2 bits) from IOStCfgB register
        config = ((readRegister(IOStCfgB)) & 0x03);
        break;
    default:
        config = ERROR;
        break;
    }
    return config;
}
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
uint8_t Max14819::readCQ(PortSelect port) {
    uint8_t state = 0;
    switch(port){
    case PORTA:
        // Return current mode (last 2 bits) from IOStCfgA register
        state = ((readRegister(IOStCfgA)) & CQLevel) >> 6;
        break;
    case PORTB:
        // Return current mode (last 2 bits) from IOStCfgB register
        state = ((readRegister(IOStCfgB)) & CQLevel) >> 6;
        break;
    default:
        state = ERROR;
        break;
    }
    return state;
}
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
uint8_t Max14819::writeCQ(PortSelect port, uint8_t value) {
    uint8_t retValue = SUCCESS;

   switch(port){
   case PORTA:
        // Set Port A CQ level
        switch (value) {
        case HIGH:
            retValue = uint8_t(retValue | writeRegister(IOStCfgA, TxEn | Tx));
            retValue = uint8_t(retValue | writeRegister(LCnfgA, LRT0 | LBL0 | LBL1 | LClimDis));
            break;
        case LOW:
            retValue = uint8_t(retValue | writeRegister(IOStCfgA, TxEn));
            retValue = uint8_t(retValue | writeRegister(LCnfgA, LRT0 | LBL0 | LBL1 | LClimDis | LEn));
            break;
        default:
            retValue = ERROR;
            break;
        } // switch(value)
        break;
    case PORTB:
        // Set Port B CQ level
        switch (value) {
        case HIGH:
            retValue = uint8_t(retValue | writeRegister(IOStCfgB, TxEn | Tx));
            retValue = uint8_t(retValue | writeRegister(LCnfgB, LRT0 | LBL0 | LBL1 | LClimDis));
            break;
        case LOW:
            retValue = uint8_t(retValue | writeRegister(IOStCfgB, TxEn));
            retValue = uint8_t(retValue | writeRegister(LCnfgB, LRT0 | LBL0 | LBL1 | LClimDis | LEn));
            break;
        default:
            retValue = ERROR;
            break;
        }
    }
    return retValue;
}
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
uint8_t Max14819::readDI(PortSelect port) {
    uint8_t state = 0;
    switch(port){
    case PORTA:
        // Return current mode (last 2 bits) from IOStCfgA register
        state = ((readRegister(IOStCfgA)) & DiLevel) >> 7;
        break;
    case PORTB:
        // Return current mode (last 2 bits) from IOStCfgB register
        state = ((readRegister(IOStCfgB)) & DiLevel) >> 7;
        break;
    default:
        state = ERROR;
        break;
    }
    return state;
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
