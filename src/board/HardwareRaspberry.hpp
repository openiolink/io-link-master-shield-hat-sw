
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
	enum PinNames {port01CS, port23CS, port01IRQ, port23IRQ, port0DI, port1DI, port2DI, port3DI,	
	port0LedGreen, port0LedRed, port0LedRxErr, port0LedRxRdy,
	port1LedGreen, port1LedRed, port1LedRxErr, port1LedRxRdy,
	port2LedGreen, port2LedRed, port2LedRxErr, port2LedRxRdy,
	port3LedGreen, port3LedRed, port3LedRxErr, port3LedRxRdy
	};

public:
	HardwareRaspberry();
	~HardwareRaspberry();

	enum PinMode { out, in_pullup, in };
	void IO_Write(PinNames pinnumber, uint8_t state);
	void IO_PinMode(PinNames pinnumber, PinMode mode); //pinMode

	void Serial_Write(char const *buf);
	void Serial_Write(int number);

	void SPI_Write(uint8_t channel, uint8_t *data, uint8_t length);

	void wait_for(uint32_t delay_ms);

	uint8_t get_pinnumber(PinNames pinname);
	void IO_Setup(void);

	class PIN_raspi : public max14819::Max14819::PIN
	{
	private:
		PinNames pinname;
		HardwareRaspberry &raspiref;
		constexpr static int LOW=0;
		constexpr static int HIGH=1;

	public:
		PIN_raspi(HardwareRaspberry &raspi, PinNames name, PinMode mode);
		// LED(PinNames name, PinMode mode, std::shared_ptr<HardwareRaspberry> hw);
		~PIN_raspi(){};
		void on(){};
		void off(){};
	};
	
};

#endif //HARDWARRASPBERRY_HPP_INCLUDED
