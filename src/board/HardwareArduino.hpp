//!*****************************************************************************
//!  \file HardwareArduino.hpp
//!  
//!  \author Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!			  	based on the work of Markus Gafner (gnm7)
//!  
//!  \brief Generic Hardware Layer abstraction of an Arduino DUE Board
//!  
//!  \date 2020-11-25
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
#ifndef HARDWARARDUINO_HPP_INCLUDED
#define HARDWARARDUINO_HPP_INCLUDED

#include "board/Max14819.hpp"
#include <stdint.h>

//! \name IO-Link Master Shield Max14819 Address
//!\{
constexpr uint8_t chip0Adresse_spi  = 0; //!< Address of chip 0
constexpr uint8_t chip1Adresse_spi  = 2; //!< Address of chip 1
//!\}

//!*****************************************************************************
//!  \brief This class describes the hardware of the Arduino DUE and the
//!         IO-Link-Master Shield/Hat
//!  
//!  
//!*****************************************************************************
class HardwareArduino
{
private:
    //!*****************************************************************************
    //!  \brief Initializes the IOs of the Arduino DUE used for the Shield/Hat
    //!  
    //!  
    //!*****************************************************************************
	void IO_Setup(void);

    //!*****************************************************************************
    //!  \brief Configures the Max14819 Chips on the Shield/Hat
    //!  
    //!  
    //!*****************************************************************************
	void configure_Max14819(void);

public:
    //!*****************************************************************************
    //!  \brief Construct a new Hardware Arduino object
    //!  
    //!  
    //!*****************************************************************************
	HardwareArduino();

    //!*****************************************************************************
    //!  \brief Destroy the Hardware Arduino object
    //!  
    //!  
    //!*****************************************************************************
	~HardwareArduino();

    //!*****************************************************************************
    //!  \brief Writes a string on the terminal
    //!  
    //!  
    //!  \param buf pointer to the string
    //!  
    //!*****************************************************************************
	void Serial_Write(char const *buf);

    //!*****************************************************************************
    //!  \brief Writes a number on the terminal
    //!  
    //!  
    //!  \param number number to write
    //!  
    //!*****************************************************************************
	void Serial_Write(int number);

    //!*****************************************************************************
    //!  \brief Waits for the given time in ms
    //!  
    //!  
    //!  \param delay_ms time to wait in ms
    //!  
    //!*****************************************************************************
	void wait_for(uint32_t delay_ms);

    //!*****************************************************************************
    //!  \brief Get pointer to the IO-Link Ports on the board
    //!  
    //!  
    //!  \param portnr number of the port
    //!  
    //!  \return shared pointer to the port
    //!  
    //!*****************************************************************************
	std::shared_ptr<openiolinklibrary::IOLMasterPort> getPort(uint8_t portnr);

    //!*****************************************************************************
    //!  \brief Implementation of the PIN class used for the Max14819
    //!  
    //!  
    //!*****************************************************************************
	class PIN_arduino : public Max14819::PIN
	{
	public:
        //!*****************************************************************************
        //!  \brief Pinnames to convert them into pinnumbers
        //!  
        //!  
        //!*****************************************************************************
		enum class PinNames {port01CS, port23CS, port01IRQ, port23IRQ, port0DI, port1DI, port2DI, port3DI,	
		port0LedGreen, port0LedRed, port0LedRxErr, port0LedRxRdy,
		port1LedGreen, port1LedRed, port1LedRxErr, port1LedRxRdy,
		port2LedGreen, port2LedRed, port2LedRxErr, port2LedRxRdy,
		port3LedGreen, port3LedRed, port3LedRxErr, port3LedRxRdy
		};

        //!*****************************************************************************
        //!  \brief Available possibilities of modes of an pin
        //!  
        //!  
        //!*****************************************************************************
		enum class PinMode { out, in_pullup, in };
	private:
		PinNames pinname;
		constexpr static int PIN_LOW=0;
		constexpr static int PIN_HIGH=1;
        //!*****************************************************************************
        //!  \brief Sets a pin to the specified logical value
        //!  
        //!  
        //!  \param pinnumber name of the Pin
        //!  
        //!  \param state state of the logical signal
        //!  
        //!*****************************************************************************
		void IO_Write(PinNames pinnumber, uint8_t state);

        //!*****************************************************************************
        //!  \brief Sets a pin to the specified mode
        //!  
        //!  
        //!  \param pinname name of the Pin
        //!  
        //!  \param mode mode of the pin
        //!  
        //!*****************************************************************************
		void IO_PinMode(PinNames pinname, PinMode mode);

        //!*****************************************************************************
        //!  \brief returns the pinnumber for the given pin (see enum PinNames)
        //!  
        //!  
        //!  \param pinname the enumerated pinname
        //!  
        //!  \return uint8_t the hardware-pinnumber
        //!  
        //!*****************************************************************************
		uint8_t get_pinnumber(PinNames pinname);

	public:
        //!*****************************************************************************
        //!  \brief Construct a new pin arduino object
        //!  
        //!  \note You have to run the function init for correct work of the object.
        //!  
        //!*****************************************************************************
		PIN_arduino(){}; // TODO remove to prevent uninitialised hw

        //!*****************************************************************************
        //!  \brief Construct a new pin arduino object
        //!  
        //!  
        //!  \param name the enumerated pinname
        //!  
        //!  \param mode of the pin
        //!  
        //!*****************************************************************************
		PIN_arduino(PinNames name, PinMode mode);

        //!*****************************************************************************
        //!  \brief Destroy the pin arduino object
        //!  
        //!  
        //!*****************************************************************************
		~PIN_arduino();

        //!*****************************************************************************
        //!  \brief Initializies the pin.
        //!  
        //!  
        //!  \param name the enumerated pinname
        //!  
        //!  \param mode of the pin
        //!  
        //!*****************************************************************************
		void init(PinNames name, PinMode mode);

        //!*****************************************************************************
        //!  \brief Set the pin to the state
        //!  
        //!  
        //!  \param state to set
        //!  
        //!*****************************************************************************
		void set(bool state);
	};

    //!*****************************************************************************
    //!  \brief Required printout for Max14819
    //!  
    //!  
    //!*****************************************************************************
	class SerialOut : public Max14819::DebugOut
	{
	private:
		/* data */
	public:
        //!*****************************************************************************
        //!  \brief Construct a new Serial Out object
        //!  
        //!  
        //!*****************************************************************************
		SerialOut(){};

        //!*****************************************************************************
        //!  \brief Destroy the Serial Out object
        //!  
        //!  
        //!*****************************************************************************
		~SerialOut(){};
        
        //!*****************************************************************************
        //!  \brief Writes a c-string to the terminal
        //!  
        //!  
        //!  \param buf pointer to the data, which gets print out
        //!  
        //!*****************************************************************************
		void print(char const * buf);
	};

    //!*****************************************************************************
    //!  \brief Required SPI class for the Max14819
    //!  
    //!  
    //!*****************************************************************************
	class SPI_arduino : public Max14819::SPI_Max14819
	{
	private:
		std::shared_ptr<PIN_arduino> cs_pin;
	public:
        //!*****************************************************************************
        //!  \brief Construct a new spi arduino object
        //!  
        //!  \note You have to run the function init for correct work of the object.
        //!  
        //!*****************************************************************************
		SPI_arduino(){}; // TODO remove to prevent uninitialised hw

        //!*****************************************************************************
        //!  \brief Construct a new spi arduino object
        //!  
        //!  
        //!  \param cs_pin_ Chip Select Pin of the Max14819 chip
        //!  
        //!*****************************************************************************
		SPI_arduino(std::shared_ptr<PIN_arduino> cs_pin_);

        //!*****************************************************************************
        //!  \brief Destroy the spi arduino object
        //!  
        //!  
        //!*****************************************************************************
		~SPI_arduino(){};

        //!*****************************************************************************
        //!  \brief Initializi the SPI interface
        //!  
        //!  
        //!  \param cs_pin_ Chip Select Pin of the Max14819 chip
        //!  
        //!*****************************************************************************
		void init(std::shared_ptr<PIN_arduino> cs_pin_);

        //!*****************************************************************************
        //!  \brief    Sends the data with the specified length and writes the
        //!            answer to the source location of the data
        //!  
        //!  \param data Pointer to the data to send. It will be overwritten with the answer
        //!  
        //!  \param length Length of the data to send and receive.
        //!  
        //!*****************************************************************************
        void DataRW(uint8_t* data, uint8_t length);
	};

    //!*****************************************************************************
    //!  \brief Class to wait some time required for the Max14819
    //!  
    //!  
    //!*****************************************************************************
	class Wait_arduino : public Max14819::Wait
	{
	private:
		/* data */
	public:
        //!*****************************************************************************
        //!  \brief Construct a new Wait_arduino object
        //!  
        //!  
        //!*****************************************************************************
		Wait_arduino(){};

        //!*****************************************************************************
        //!  \brief Destroy the Wait_arduino object
        //!  
        //!  
        //!*****************************************************************************
		~Wait_arduino(){};

        //!*****************************************************************************
        //!  \brief Waits for the given time in ms
        //!  
        //!  
        //!  \param time_ms time to wait in ms
        //!  
        //!*****************************************************************************
		void ms(uint32_t time_ms);
	};

    //! \name Pins on the Arduino DUE of chip 0
    //!\{
    PIN_arduino CS_chip0;  //!< ChipSelect
    PIN_arduino IRQ_chip0; //!< Interrupt Output
    PIN_arduino DI0;       //!< Digital Input of port A
    PIN_arduino DI1;       //!< Digital Input of port B
    //!\}

    //! \name Pins on the Arduino DUE of chip 1
    //!\{
	PIN_arduino CS_chip1; //!< ChipSelect 
	PIN_arduino IRQ_chip1; //!< Interrupt Output 
	PIN_arduino DI2; //!< Digital Input of port 
	PIN_arduino DI3; //!< Digital Input of port 
    //!\}

    //! \name LEDs at Port A
    //!\{
    PIN_arduino RxErrLED0; //!< Rx Error LED
    PIN_arduino RxRdyLED0; //!< Rx Ready LED
    PIN_arduino redLED0;   //!< Red LED
    PIN_arduino greenLED0; //!< Green LED
    //!\}

    //! \name LEDs at Port B
    //!\{
    PIN_arduino RxErrLED1; //!< Rx Error LED
    PIN_arduino RxRdyLED1; //!< Rx Ready LED
    PIN_arduino redLED1;   //!< Red LED
    PIN_arduino greenLED1; //!< Green LED
    //!\}

    //! \name LEDs at Port C
    //!\{
    PIN_arduino RxErrLED2; //!< Rx Error LED
	PIN_arduino RxRdyLED2; //!< Rx Ready LED
	PIN_arduino redLED2;   //!< Red LED
	PIN_arduino greenLED2; //!< Green LED
    //!\}

    //! \name LEDs at Port D
    //!\{
	PIN_arduino RxErrLED3; //!< Rx Error LED
	PIN_arduino RxRdyLED3; //!< Rx Ready LED
	PIN_arduino redLED3;   //!< Red LED
	PIN_arduino greenLED3; //!< Green LED
    //!\}

	SerialOut serialout; //!< Object to printout on terminal used for Max14819
	
    //! \name SPI interfaces on the Board
    //!\{
    SPI_arduino spi0;     //!< SPI Object used for Max14819 chip 0
    SPI_arduino spi1;     //!< SPI Object used for Max14819 chip 1
    //!\}
	
    Wait_arduino wait_arduino;  //!< Object to wait some time used for Max14819
	
    //! \name Max14819 chips on the Board
    //!\{
    std::shared_ptr<Max14819> IOLChip0; //!< Chip 0 on the board
	std::shared_ptr<Max14819> IOLChip1; //!< Chip 1 on the board
    //!\}
	
    //! \name IO-Link Ports on the board
    //!\{
	std::shared_ptr<openiolinklibrary::IOLMasterPort> PORT0; //!< Pointer to port0 on the board
	std::shared_ptr<openiolinklibrary::IOLMasterPort> PORT1; //!< Pointer to port1 on the board
	std::shared_ptr<openiolinklibrary::IOLMasterPort> PORT2; //!< Pointer to port2 on the board
	std::shared_ptr<openiolinklibrary::IOLMasterPort> PORT3; //!< Pointer to port3 on the board
    //!\}
};

#endif //HARDWARARDUINO_HPP_INCLUDED