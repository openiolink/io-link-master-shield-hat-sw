
//!*****************************************************************************
//!  \file      HardwareRaspberry.h
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
#ifndef HARDWARRASPBERRY_HPP_INCLUDED
#define HARDWARRASPBERRY_HPP_INCLUDED

//!**** Header-Files ************************************************************
#include "protocol/HardwareBase.hpp"
#include "board/Max14819.hpp"
#include <cstdint>
//!**** Macros ******************************************************************

//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************

//!**** Data ********************************************************************

//!**** Implementation **********************************************************

class HardwareRaspberry : public HardwareBase
{
private:

public:
	HardwareRaspberry();
	~HardwareRaspberry();


	void Serial_Write(char const *buf);
	void Serial_Write(int number);

	void SPI_Write(uint8_t channel, uint8_t *data, uint8_t length);

	void wait_for(uint32_t delay_ms);

	void IO_Setup(void);

	class PIN_raspi : public max14819::Max14819::PIN
	{
	public:
		enum class PinNames {port01CS, port23CS, port01IRQ, port23IRQ, port0DI, port1DI, port2DI, port3DI,	
		port0LedGreen, port0LedRed, port0LedRxErr, port0LedRxRdy,
		port1LedGreen, port1LedRed, port1LedRxErr, port1LedRxRdy,
		port2LedGreen, port2LedRed, port2LedRxErr, port2LedRxRdy,
		port3LedGreen, port3LedRed, port3LedRxErr, port3LedRxRdy
		};
		enum PinMode { out, in_pullup, in };
	private:
		PinNames pinname;
		constexpr static int LOW=0;
		constexpr static int HIGH=1;
		void IO_Write(PinNames pinnumber, uint8_t state);
		void IO_PinMode(PinNames pinnumber, PinMode mode); //pinMode
		uint8_t get_pinnumber(PinNames pinname);

	public:

		PIN_raspi(){};
		PIN_raspi(PinNames name, PinMode mode);
		~PIN_raspi();
		void init(PinNames name, PinMode mode);
		void set(bool state);
	};

	class SerialOut : public max14819::Max14819::DebugOut
	{
	private:
		/* data */
	public:
		SerialOut(/* args */){};
		~SerialOut(){};
		void print(char const * buf);
	};


	PIN_raspi CS_chip0;
	PIN_raspi IRQ_chip0;
	PIN_raspi DI0;
	PIN_raspi DI1;
	PIN_raspi redLED0;
	PIN_raspi greenLED0;
	PIN_raspi RxErrLED0;
	PIN_raspi RxRdyLED0;
	PIN_raspi redLED1;
	PIN_raspi greenLED1;
	PIN_raspi RxErrLED1;
	PIN_raspi RxRdyLED1;
	
	PIN_raspi CS_chip1;
	PIN_raspi IRQ_chip1;
	PIN_raspi DI2;
	PIN_raspi DI3;
	PIN_raspi redLED2;
	PIN_raspi greenLED2;
	PIN_raspi RxErrLED2;
	PIN_raspi RxRdyLED2;
	PIN_raspi redLED3;
	PIN_raspi greenLED3;
	PIN_raspi RxErrLED3;
	PIN_raspi RxRdyLED3;

	SerialOut serialout;
	// max14819::Max14819 IOLChip1(std::shared_ptr<SerialOut>);
	
};

#endif //HARDWARRASPBERRY_HPP_INCLUDED
