//!*****************************************************************************
//!  \file      HardwareRaspberry.cpp
//!*****************************************************************************
//!
//!  \brief		Generic Hardware Layer abstraction of a physical layer
//!
//!  \author    Markus Gafner (gnm7)
//!
//!  \date      2019-09-13
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
#include "HardwareRaspberry.hpp"

#include <wiringPi.h>
#include <wiringPiSPI.h>		// Needed for SPI communication

#include <stdio.h>
#include <unistd.h>
#include <iostream>				// Needed for File-IO
#include <fstream>				// Needed for File-IO
#include <fcntl.h>   			// Needed for SPI port
#include <sys/ioctl.h>			// Needed for SPI port
#include <linux/spi/spidev.h>	// Needed for SPI port
//int wiringPiSPIGetFd     (int channel) ;
//int wiringPiSPIDataRW    (int channel, unsigned char *data, int len) ;
//int wiringPiSPISetupMode (int channel, int speed, int mode) ;
//int wiringPiSPISetup     (int channel, int speed) ;

//!**** Macros ******************************************************************

//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************

//!**** Data ********************************************************************

//!**** Implementation **********************************************************




HardwareRaspberry::HardwareRaspberry()
{
	// Init Wiring Pi
	wiringPiSetup();

	// Init SPI
	Serial_Write("Init_SPI starts");
	wiringPiSPISetup(0, 500000); //chip 1
	wiringPiSPISetup(1, 500000); //chip 2

	Serial_Write("Init_SPI finished");
	wait_for(1*1000);
	IO_Setup();
}


HardwareRaspberry::~HardwareRaspberry()
{
	//Deinit SPI
	// TODO
}

void HardwareRaspberry::IO_Setup(void)
{
	// DRIVER0
	CS_chip0.init(PIN_raspi::PinNames::port01CS, PIN_raspi::PinMode::out);
	IRQ_chip0.init(PIN_raspi::PinNames::port01IRQ, PIN_raspi::PinMode::in_pullup);
	DI0.init(PIN_raspi::PinNames::port0DI, PIN_raspi::PinMode::in_pullup);
	DI1.init(PIN_raspi::PinNames::port1DI, PIN_raspi::PinMode::in_pullup);
	redLED0.init(PIN_raspi::PinNames::port0LedRed, PIN_raspi::PinMode::out);
	greenLED0.init(PIN_raspi::PinNames::port0LedGreen, PIN_raspi::PinMode::out);
	RxErrLED0.init(PIN_raspi::PinNames::port0LedRxErr, PIN_raspi::PinMode::in_pullup);
	RxRdyLED0.init(PIN_raspi::PinNames::port0LedRxRdy, PIN_raspi::PinMode::in_pullup);
	redLED1.init(PIN_raspi::PinNames::port1LedRed, PIN_raspi::PinMode::out);
	greenLED1.init(PIN_raspi::PinNames::port1LedGreen, PIN_raspi::PinMode::out);
	RxErrLED1.init(PIN_raspi::PinNames::port1LedRxErr, PIN_raspi::PinMode::in_pullup);
	RxRdyLED1.init(PIN_raspi::PinNames::port1LedRxRdy, PIN_raspi::PinMode::in_pullup);
	
	redLED0.off();
	greenLED0.off();
	redLED1.off();
	greenLED1.off();
	
	// DRIVER1
	CS_chip1.init(PIN_raspi::PinNames::port23CS, PIN_raspi::PinMode::out);
	IRQ_chip1.init(PIN_raspi::PinNames::port23IRQ, PIN_raspi::PinMode::in_pullup);
	DI2.init(PIN_raspi::PinNames::port2DI, PIN_raspi::PinMode::in_pullup);
	DI3.init(PIN_raspi::PinNames::port3DI, PIN_raspi::PinMode::in_pullup);
	redLED2.init(PIN_raspi::PinNames::port2LedRed, PIN_raspi::PinMode::out);
	greenLED2.init(PIN_raspi::PinNames::port2LedGreen, PIN_raspi::PinMode::out);
	RxErrLED2.init(PIN_raspi::PinNames::port2LedRxErr, PIN_raspi::PinMode::in_pullup);
	RxRdyLED2.init(PIN_raspi::PinNames::port2LedRxRdy, PIN_raspi::PinMode::in_pullup);
	redLED3.init(PIN_raspi::PinNames::port3LedRed, PIN_raspi::PinMode::out);
	greenLED3.init(PIN_raspi::PinNames::port3LedGreen, PIN_raspi::PinMode::out);
	RxErrLED3.init(PIN_raspi::PinNames::port3LedRxErr, PIN_raspi::PinMode::in_pullup);
	RxRdyLED3.init(PIN_raspi::PinNames::port3LedRxRdy, PIN_raspi::PinMode::in_pullup);
	
	redLED2.on();
	greenLED2.on();
	redLED3.on();
	greenLED3.on();
	
    //TODO retValue = uint8_t(retValue | writeRegister(Clock, TXTXENDis | ClkOEn | XtalEn)); // Frequency is 14.745 MHz

    // TODO Reset max14819 register
    // retValue = uint8_t(retValue | reset(port));

    // TODO Wait 1 s for turning on the powersupply for sensor
	// Hardware->wait_for(INIT_POWER_OFF_DELAY);

	
    // TODO Initialize global registers
    // retValue = uint8_t(retValue | writeRegister(DrvrCurrLim, CL1 | CL0 | CLBL1 | CLBL0 | ArEn)); //CQ 500 mA currentlimit, 5 ms min error duration before interrupt

}



//!*****************************************************************************
//!function :      Serial_Write
//!*****************************************************************************
//!  \brief        Writes a c-string to the serial connection
//!
//!  \type         local
//!
//!  \param[in]	   char const * pointer to the data, which gets print out
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareRaspberry::Serial_Write(char const * buf)
{
	printf("%s\n", buf);
}

//!*****************************************************************************
//!function :      Serial_Write
//!*****************************************************************************
//!  \brief        Writes a number to the serial connection
//!
//!  \type         local
//!
//!  \param[in]	   int	      the number which should get printed
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareRaspberry::Serial_Write(int number)
{
	printf("%d\n", number);
}

//!*****************************************************************************
//!function :      SPI_Write
//!*****************************************************************************
//!  \brief        Writes some data to the specified SPI-Connection
//!
//!  \type         local
//!
//!  \param[in]	   uint8_t    channel number
//!				   uint8_t*   pointer to the data structure
//!				   uint8_t    length of the data in bytes
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareRaspberry::SPI_Write(uint8_t channel, uint8_t * data, uint8_t length)
{
	//printf("SPI sending: %x, %x  ", data[0], data[1]);
	wiringPiSPIDataRW(channel, data, length);
	//printf("received %x,%x\n", data[0], data[1]);
}

//!*****************************************************************************
//!function :      wait_for
//!*****************************************************************************
//!  \brief        delay the thread for the given time
//!
//!  \type         local
//!
//!  \param[in]	   uint32_t    delay time im miliseconds
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareRaspberry::wait_for(uint32_t delay_ms)
{
	//printf("Sleep_in\n");
	usleep(delay_ms*1000);
	//printf("Sleep_out\n");
}


HardwareRaspberry::PIN_raspi::PIN_raspi(PinNames name, PinMode mode){
	this->init(name, mode);
}

HardwareRaspberry::PIN_raspi::~PIN_raspi(){
	IO_PinMode(pinname, in);
}

void HardwareRaspberry::PIN_raspi::init(PinNames name, PinMode mode){
	pinname = name;
	IO_PinMode(name, mode);
}

void HardwareRaspberry::PIN_raspi::on(){
	IO_Write(pinname, LOW);
}

void HardwareRaspberry::PIN_raspi::off(){
	IO_Write(pinname, HIGH);
}

//!*****************************************************************************
//!function :      get_pinnumber
//!*****************************************************************************
//!  \brief        returns the pinnumber for the given pin (see enum PinNames)
//!
//!  \type         local
//!
//!  \param[in]	   PinNames    the enumerated pinname
//!
//!  \return       the hardware-pinnumber
//!
//!*****************************************************************************
uint8_t HardwareRaspberry::PIN_raspi::get_pinnumber(PinNames pinname)
{
	switch (pinname) {
		case PinNames::port01CS:		return 31u;			//SPI_CS0	(Pin24, output)
		case PinNames::port23CS:		return 31u;			//SPI_CS1	(Pin26, output)
		case PinNames::port01IRQ:		return 0u;			//P01_IRQ	(Pin11, input)
		case PinNames::port23IRQ:		return 4u;			//P23_IRQ	(Pin16, input)
		case PinNames::port0DI:		return 7u;			//P0_DI     (Pin 7, input)
		case PinNames::port1DI:		return 15u;			//P1_DI     (Pin 8, input)
		case PinNames::port2DI:		return 16u;			//P2_DI     (Pin 10, input)
		case PinNames::port3DI:		return 30u;			//P3_DI     (Not avaiable)

		case PinNames::port0LedGreen: return 9u;			//P1_LED_GN	(Pin 5, output)
		case PinNames::port0LedRed:	return 8u;			//P1_LED_RD	(Pin 3, output)
		case PinNames::port0LedRxErr:	return 23u;			//P0_RX_ERR	(Pin33, input, pullup)
		case PinNames::port0LedRxRdy:	return 24u;			//P0_RX_RDY (Pin35, input, pullup)	

		case PinNames::port1LedGreen: return 21u;			//P0_LED_GN	(Pin29, output)
		case PinNames::port1LedRed:	return 22u;			//P0_LED_RD	(Pin31, output)
		case PinNames::port1LedRxErr:	return 2u;			//P1_RX_ERR	(Pin13, input, pullup)
		case PinNames::port1LedRxRdy:	return 3u;			//P1_RX_RDY (Pin15, input, pullup)	

		case PinNames::port2LedGreen: return 25u;			//P3_LED_GN	(Pin37, output)
		case PinNames::port2LedRed:	return 1u;			//P3_LED_RD	(Pin12, output)
		case PinNames::port2LedRxErr:	return 27u;			//P2_RX_ERR	(Pin36, input, pullup)
		case PinNames::port2LedRxRdy:	return 26u;			//P2_RX_RDY (Pin32, input, pullup)	
 
		case PinNames::port3LedGreen: return 29u;			//P2_LED_GN	(Pin40, output)
		case PinNames::port3LedRed:	return 5u;			//P2_LED_RD	(Pin18, output)
		case PinNames::port3LedRxErr:	return 6u;			//P3_RX_ERR	(Pin22, input, pullup)
		case PinNames::port3LedRxRdy:	return 28u;			//P3_RX_RDY (Pin38, input, pullup)	
	}
	return uint8_t();
}

//!*****************************************************************************
//!function :      IO_Write
//!*****************************************************************************
//!  \brief        Sets a pin to the specified logical value
//!
//!  \type         local
//!
//!  \param[in]	   PinNames   name of the Pin
//!  			   uint8_t    state of the logical signal
//!
//!  \return       void
//!
//!*****************************************************************************

void HardwareRaspberry::PIN_raspi::IO_Write(PinNames pinname, uint8_t state)
{
	uint8_t pinnumber = get_pinnumber(pinname);
	switch (state) {
		case HIGH	: digitalWrite(pinnumber, HIGH); break;
		case LOW	: digitalWrite(pinnumber, LOW); break;
	}
}

//!*****************************************************************************
//!function :      IO_PinMode
//!*****************************************************************************
//!  \brief        Sets a pin to the specified mode
//!
//!  \type         local
//!
//!  \param[in]	   PinNames   name of the Pin
//!  			   PinMode    mode of the pin
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareRaspberry::PIN_raspi::IO_PinMode(PinNames pinname, PinMode mode)
{
	uint8_t pinnumber = get_pinnumber(pinname);
	switch (mode) {
	case out: 
		pinMode(pinnumber, OUTPUT);
		break;
	case in_pullup: 
		pinMode(pinnumber, INPUT);
		pullUpDnControl(pinnumber, PUD_UP);
		break;
	case in:
		pinMode(pinnumber, INPUT);
		pullUpDnControl(pinnumber, PUD_OFF);
		break;
}
}

// HardwareRaspberry::SPI_raspi::SPI_raspi(uint8_t channel_) : channel(channel_) {
// 	if (channel > 1)
// 	{
// 		channel = 1;
// 	}
// 	wiringPiSPISetup(channel, 500000);
// }