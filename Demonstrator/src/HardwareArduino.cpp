
//!*****************************************************************************
//!  \file      HardwareArduino.cpp
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
#include "HardwareArduino.h"
#include <Arduino.h>
#include <SPI.h>
#include <stdio.h>

//!**** Macros ******************************************************************

//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************

//!**** Data ********************************************************************

//!**** Implementation **********************************************************

HardwareArduino::HardwareArduino()
{
    // Define all SPI signals for the Geckoboard as inputs. if not, MOSI cant be thrown to 0V
    pinMode(50, in);
    pinMode(52, in);
    pinMode(53, in);
}


HardwareArduino::~HardwareArduino()
{
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
void HardwareArduino::begin(){

	Serial.begin(115200);

	Serial.print("\nBeginne mit der Initialisierung\n");

	SPI.begin();
	SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
	delay(1000);

	Serial_Write("Init_SPI finished");
	wait_for(1*1000);
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
void HardwareArduino::IO_Write(PinNames pinname, uint8_t state)
{
    uint8_t pinnumber = get_pinnumber(pinname);
	digitalWrite(pinnumber, state);
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
void HardwareArduino::IO_PinMode(PinNames pinname, PinMode mode)
{
    uint8_t pinnumber = get_pinnumber(pinname);
	switch (mode) {
	case out      : pinMode(pinnumber, OUTPUT); break;
	case in_pullup: pinMode(pinnumber, INPUT_PULLUP); break;
	case in       : pinMode(pinnumber, INPUT); break;
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
void HardwareArduino::Serial_Write(char const * buf)
{
	Serial.println(buf);
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
void HardwareArduino::Serial_Write(int number)
{
	Serial.print(number);
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
void HardwareArduino::SPI_Write(uint8_t channel, uint8_t * data, uint8_t length)
{
    switch(channel){
        case 0:
            // Enable chipselect -> output high (low-active)
            IO_Write(port01CS, LOW);
            break;
        case 1:
            // Enable chipselect -> output high (low-active)
            IO_Write(port23CS, LOW);
            break;
    }


    for(int i = 0; i<length; i++){
        data[i] = SPI.transfer(data[i]);
    }

    // Disable chipselect -> output high (low-active)
    IO_Write(port01CS, HIGH);
    IO_Write(port23CS, HIGH);
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
void HardwareArduino::wait_for(uint32_t delay_ms)
{
    delay(delay_ms);
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
uint8_t HardwareArduino::get_pinnumber(PinNames pinname)
{
	switch (pinname) {
		case port01CS:		return 10u;
		case port23CS:		return 4u;
		case port01IRQ:		return 5u;
		case port23IRQ:		return 11u;
		case port0DI:		return 55u;
		case port1DI:		return 54u;
		case port2DI:		return 14u;
		case port3DI:		return 15u;

		case port0LedGreen: return 2u;
		case port0LedRed:	return 3u;
		case port0LedRxErr:	return 61u;
		case port0LedRxRdy:	return 60u;

		case port1LedGreen: return 56u;
		case port1LedRed:	return 57u;
		case port1LedRxErr:	return 58u;
		case port1LedRxRdy:	return 59u;

		case port2LedGreen: return 6u;
		case port2LedRed:	return 7u;
		case port2LedRxErr:	return 9u;
		case port2LedRxRdy:	return 8u;

		case port3LedGreen: return 71u;
		case port3LedRed:	return 70u;
		case port3LedRxErr:	return 13u;
		case port3LedRxRdy:	return 12u;
	}
	return uint8_t();
}