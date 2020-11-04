
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

    // IO-Link Master Shield Max14819 Address
    constexpr uint8_t chip0Adresse_spi  = 0;
    constexpr uint8_t chip1Adresse_spi  = 2;
//!**** Data types **************************************************************

//!**** Function prototypes *****************************************************

//!**** Data ********************************************************************

//!**** Implementation **********************************************************

class HardwareRaspberry : public HardwareBase
{
private:
	void IO_Setup(void);
	void configure_Max14819(void);

public:
	HardwareRaspberry();
	~HardwareRaspberry();


	void Serial_Write(char const *buf);
	void Serial_Write(int number);

	void SPI_Write(uint8_t channel, uint8_t *data, uint8_t length);

	void wait_for(uint32_t delay_ms);


	class PIN_raspi : public Max14819::PIN
	{
	public:
		enum class PinNames {port01CS, port23CS, port01IRQ, port23IRQ, port0DI, port1DI, port2DI, port3DI,	
		port0LedGreen, port0LedRed, port0LedRxErr, port0LedRxRdy,
		port1LedGreen, port1LedRed, port1LedRxErr, port1LedRxRdy,
		port2LedGreen, port2LedRed, port2LedRxErr, port2LedRxRdy,
		port3LedGreen, port3LedRed, port3LedRxErr, port3LedRxRdy
		};
		enum class PinMode { out, in_pullup, in };
	private:
		PinNames pinname;
		constexpr static int LOW=0;
		constexpr static int HIGH=1;
		void IO_Write(PinNames pinnumber, uint8_t state);
		void IO_PinMode(PinNames pinnumber, PinMode mode); //pinMode
		uint8_t get_pinnumber(PinNames pinname);

	public:

		PIN_raspi(){}; // TODO remove to prevent uninitialised hw
		PIN_raspi(PinNames name, PinMode mode);
		~PIN_raspi();
		void init(PinNames name, PinMode mode);
		void set(bool state);
	};

	class SerialOut : public Max14819::DebugOut
	{
	private:
		/* data */
	public:
		SerialOut(/* args */){};
		~SerialOut(){};
		void print(char const * buf);
	};

	class SPI_raspi : public Max14819::SPI
	{
	private:
		constexpr static int spi_speed=500000;
		uint8_t channel;
		std::shared_ptr<PIN_raspi> cs_pin;
	public:
		SPI_raspi(){}; // TODO remove to prevent uninitialised hw
		SPI_raspi(uint8_t channel_, std::shared_ptr<PIN_raspi> cs_pin_);
		~SPI_raspi(){};
		void init(uint8_t channel_, std::shared_ptr<PIN_raspi> cs_pin_);
        void DataRW(uint8_t* data, uint8_t length);
	};

	class Wait_raspi : public Max14819::Wait // awo make abstract
	{
	private:
		/* data */
	public:
		Wait_raspi(/* args */){};
		~Wait_raspi(){};
		void ms(uint32_t time_ms);
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
	SPI_raspi spi0;
	SPI_raspi spi1;
	Wait_raspi wait_raspi;
	std::shared_ptr<Max14819> IOLChip0;
	std::shared_ptr<Max14819> IOLChip1;
	
	std::shared_ptr<openiolinklibrary::IOLMasterPort> PORT0;
	std::shared_ptr<openiolinklibrary::IOLMasterPort> PORT1;
	std::shared_ptr<openiolinklibrary::IOLMasterPort> PORT2;
	std::shared_ptr<openiolinklibrary::IOLMasterPort> PORT3;
	
};

#endif //HARDWARRASPBERRY_HPP_INCLUDED
