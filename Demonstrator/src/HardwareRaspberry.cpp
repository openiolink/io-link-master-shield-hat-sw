#ifndef ARDUINO

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
#include "HardwareRaspberry.h"
#include <stdio.h>
#include <unistd.h>

#include <iostream>				// Needed for File-IO
#include <fstream>				// Needed for File-IO

#include <wiringPi.h>

#include <fcntl.h>   			// Needed for SPI port
#include <sys/ioctl.h>			// Needed for SPI port
#include <linux/spi/spidev.h>	// Needed for SPI port

#include <wiringPiSPI.h>		// Needed for SPI communication
//int wiringPiSPIGetFd     (int channel) ;
//int wiringPiSPIDataRW    (int channel, unsigned char *data, int len) ;
//int wiringPiSPISetupMode (int channel, int speed, int mode) ;
//int wiringPiSPISetup     (int channel, int speed) ;

//!**** Macros ******************************************************************
#define LOW 0
#define HIGH 1

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
	wiringPiSPISetup(0, 500000);
	wiringPiSPISetup(1, 500000);

	Serial_Write("Init_SPI finished");
	wait_for(1*1000);
}


HardwareRaspberry::~HardwareRaspberry()
{
	//Deinit SPI
	// TODO
}

//!*****************************************************************************
//!function :      begin
//!*****************************************************************************
//!  \brief        Initialices the Class after generation
//!
//!  \type         local
//!
//!  \param[in]	   void
//!
//!  \return       void
//!
//!*****************************************************************************
void HardwareRaspberry::begin(){

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

void HardwareRaspberry::IO_Write(PinNames pinname, uint8_t state)
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
void HardwareRaspberry::IO_PinMode(PinNames pinname, PinMode mode)
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
uint8_t HardwareRaspberry::get_pinnumber(PinNames pinname)
{
	switch (pinname) {
		case port01CS:		return 31u;			//SPI_CS0	(Pin24, output)
		case port23CS:		return 31u;			//SPI_CS1	(Pin26, output)
		case port01IRQ:		return 0u;			//P01_IRQ	(Pin11, input)
		case port23IRQ:		return 4u;			//P23_IRQ	(Pin16, input)
		case port0DI:		return 7u;			//P0_DI     (Pin 7, input)
		case port1DI:		return 15u;			//P1_DI     (Pin 8, input)
		case port2DI:		return 16u;			//P2_DI     (Pin 10, input)
		case port3DI:		return 30u;			//P3_DI     (Not avaiable)

		case port0LedGreen: return 9u;			//P1_LED_GN	(Pin 5, output)
		case port0LedRed:	return 8u;			//P1_LED_RD	(Pin 3, output)
		case port0LedRxErr:	return 23u;			//P0_RX_ERR	(Pin33, input, pullup)
		case port0LedRxRdy:	return 24u;			//P0_RX_RDY (Pin35, input, pullup)	

		case port1LedGreen: return 21u;			//P0_LED_GN	(Pin29, output)
		case port1LedRed:	return 22u;			//P0_LED_RD	(Pin31, output)
		case port1LedRxErr:	return 2u;			//P1_RX_ERR	(Pin13, input, pullup)
		case port1LedRxRdy:	return 3u;			//P1_RX_RDY (Pin15, input, pullup)	

		case port2LedGreen: return 25u;			//P3_LED_GN	(Pin37, output)
		case port2LedRed:	return 1u;			//P3_LED_RD	(Pin12, output)
		case port2LedRxErr:	return 27u;			//P2_RX_ERR	(Pin36, input, pullup)
		case port2LedRxRdy:	return 26u;			//P2_RX_RDY (Pin32, input, pullup)	
 
		case port3LedGreen: return 29u;			//P2_LED_GN	(Pin40, output)
		case port3LedRed:	return 5u;			//P2_LED_RD	(Pin18, output)
		case port3LedRxErr:	return 6u;			//P3_RX_ERR	(Pin22, input, pullup)
		case port3LedRxRdy:	return 28u;			//P3_RX_RDY (Pin38, input, pullup)	
	}
	return uint8_t();
}
#endif
