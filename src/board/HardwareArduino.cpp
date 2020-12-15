//!*****************************************************************************
//!  \file HardwareArduino.cpp
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

#include "HardwareArduino.hpp"
#include <Arduino.h>
#include <SPI.h>
#include <stdio.h>

HardwareArduino::HardwareArduino()
{	
	IO_Setup();
	Serial.begin(115200);
	delay(100);
	Serial.print("\n\rBeginne mit der Initialisierung\n\r");
	Serial.flush();
	// Init SPI
	Serial.print("Init_SPI starts\n\r");
	SPI.begin();
	SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
	spi0.init(std::make_shared<PIN_arduino>(CS_chip0));
	spi1.init(std::make_shared<PIN_arduino>(CS_chip1));
	Serial.print("Init_SPI finished\n\r");
	delay(1*1000);
	IOLChip0 = std::make_shared<Max14819>(Max14819(std::make_shared<SerialOut>(serialout), std::make_shared<SPI_arduino>(spi0), chip0Adresse_spi, std::make_shared<Wait_arduino>(wait_arduino)));
	IOLChip1 = std::make_shared<Max14819>(Max14819(std::make_shared<SerialOut>(serialout), std::make_shared<SPI_arduino>(spi1), chip1Adresse_spi, std::make_shared<Wait_arduino>(wait_arduino)));

	configure_Max14819();
	IOLChip0->initPorts();
	IOLChip1->initPorts();

	PORT0 = IOLChip0->getPort(Max14819::Max14819_Port::PortNr::PORTA);
	PORT1 = IOLChip0->getPort(Max14819::Max14819_Port::PortNr::PORTB);
	PORT2 = IOLChip1->getPort(Max14819::Max14819_Port::PortNr::PORTA);
	PORT3 = IOLChip1->getPort(Max14819::Max14819_Port::PortNr::PORTB);
}


HardwareArduino::~HardwareArduino()
{
}

void HardwareArduino::IO_Setup()
{
	// DRIVER0
	CS_chip0.init(PIN_arduino::PinNames::port01CS, PIN_arduino::PinMode::out);
	CS_chip0.set(false);
	IRQ_chip0.init(PIN_arduino::PinNames::port01IRQ, PIN_arduino::PinMode::in_pullup);
	DI0.init(PIN_arduino::PinNames::port0DI, PIN_arduino::PinMode::in_pullup);
	DI1.init(PIN_arduino::PinNames::port1DI, PIN_arduino::PinMode::in_pullup);
	redLED0.init(PIN_arduino::PinNames::port0LedRed, PIN_arduino::PinMode::out);
	greenLED0.init(PIN_arduino::PinNames::port0LedGreen, PIN_arduino::PinMode::out);
	RxErrLED0.init(PIN_arduino::PinNames::port0LedRxErr, PIN_arduino::PinMode::in_pullup);
	RxRdyLED0.init(PIN_arduino::PinNames::port0LedRxRdy, PIN_arduino::PinMode::in_pullup);
	redLED1.init(PIN_arduino::PinNames::port1LedRed, PIN_arduino::PinMode::out);
	greenLED1.init(PIN_arduino::PinNames::port1LedGreen, PIN_arduino::PinMode::out);
	RxErrLED1.init(PIN_arduino::PinNames::port1LedRxErr, PIN_arduino::PinMode::in_pullup);
	RxRdyLED1.init(PIN_arduino::PinNames::port1LedRxRdy, PIN_arduino::PinMode::in_pullup);
	
	redLED0.set(false);
	greenLED0.set(false);
	redLED1.set(false);
	greenLED1.set(false);
	
	// DRIVER1
	CS_chip1.init(PIN_arduino::PinNames::port23CS, PIN_arduino::PinMode::out);
	CS_chip1.set(false);
	IRQ_chip1.init(PIN_arduino::PinNames::port23IRQ, PIN_arduino::PinMode::in_pullup);
	DI2.init(PIN_arduino::PinNames::port2DI, PIN_arduino::PinMode::in_pullup);
	DI3.init(PIN_arduino::PinNames::port3DI, PIN_arduino::PinMode::in_pullup);
	redLED2.init(PIN_arduino::PinNames::port2LedRed, PIN_arduino::PinMode::out);
	greenLED2.init(PIN_arduino::PinNames::port2LedGreen, PIN_arduino::PinMode::out);
	RxErrLED2.init(PIN_arduino::PinNames::port2LedRxErr, PIN_arduino::PinMode::in_pullup);
	RxRdyLED2.init(PIN_arduino::PinNames::port2LedRxRdy, PIN_arduino::PinMode::in_pullup);
	redLED3.init(PIN_arduino::PinNames::port3LedRed, PIN_arduino::PinMode::out);
	greenLED3.init(PIN_arduino::PinNames::port3LedGreen, PIN_arduino::PinMode::out);
	RxErrLED3.init(PIN_arduino::PinNames::port3LedRxErr, PIN_arduino::PinMode::in_pullup);
	RxRdyLED3.init(PIN_arduino::PinNames::port3LedRxRdy, PIN_arduino::PinMode::in_pullup);
	
	redLED2.set(false);
	greenLED2.set(false);
	redLED3.set(false);
	greenLED3.set(false);
}

void HardwareArduino::configure_Max14819()
{
    uint8_t shadowReg = 0;
	// Enable extern crystal
	IOLChip0->writeRegister(Max14819::Clock, Max14819::TXTXENDis | Max14819::ClkOEn | Max14819::XtalEn); // Frequency is 14.745 MHz

	// Enable clocking from another max14819
	IOLChip1->writeRegister(Max14819::Clock, Max14819::TXTXENDis | Max14819::ExtClkEn | Max14819::ClkDiv0 | Max14819::ClkDiv1); // external OSC enable, 3.686 MHz input frequency
	
	IOLChip0->reset();
	IOLChip1->reset();
	
    // Wait 1 s for turning on the powersupply for sensor
	wait_for(Max14819::INIT_POWER_OFF_DELAY);

    IOLChip0->writeRegister(Max14819::DrvrCurrLim, Max14819::CL1 | Max14819::CL0 | Max14819::CLBL1 | Max14819::CLBL0 | Max14819::ArEn); //CQ 500 mA currentlimit, 5 ms min error duration before interrupt
    IOLChip1->writeRegister(Max14819::DrvrCurrLim, Max14819::CL1 | Max14819::CL0 | Max14819::CLBL1 | Max14819::CLBL0 | Max14819::ArEn); //CQ 500 mA currentlimit, 5 ms min error duration before interrupt

    // Initialize the port sepcific registers
	// PortA
    shadowReg = IOLChip0->readRegister(Max14819::InterruptEn);
    IOLChip0->writeRegister(Max14819::InterruptEn, Max14819::StatusIntEn | Max14819::WURQIntEn | Max14819::TxErrIntEnA | Max14819::RxErrIntEnA | Max14819::RxDaRdyIntEnA | shadowReg);

    shadowReg = IOLChip1->readRegister(Max14819::InterruptEn);
    IOLChip1->writeRegister(Max14819::InterruptEn, Max14819::StatusIntEn | Max14819::WURQIntEn | Max14819::TxErrIntEnA | Max14819::RxErrIntEnA | Max14819::RxDaRdyIntEnA | shadowReg);

	// Enable LedRxRdy and RyError LED
	shadowReg = IOLChip0->readRegister(Max14819::LEDCtrl);
	IOLChip0->writeRegister(Max14819::LEDCtrl, Max14819::RxRdyEnA | Max14819::RxErrEnA | shadowReg);
	// Initialize the Port A register
	IOLChip0->writeRegister(Max14819::LCnfgA, Max14819::LRT0 | Max14819::LBL0 | Max14819::LBL1 | Max14819::LClimDis | Max14819::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
	IOLChip0->writeRegister(Max14819::CQCfgA, Max14819::SinkSel0 | Max14819::PushPul); // Int Current Sink, 5 mA, PushPull, Channel Enable

	shadowReg = IOLChip1->readRegister(Max14819::LEDCtrl);
	IOLChip1->writeRegister(Max14819::LEDCtrl, Max14819::RxRdyEnA | Max14819::RxErrEnA | shadowReg);
	// Initialize the Port A register
	IOLChip1->writeRegister(Max14819::LCnfgA, Max14819::LRT0 | Max14819::LBL0 | Max14819::LBL1 | Max14819::LClimDis | Max14819::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
	IOLChip1->writeRegister(Max14819::CQCfgA, Max14819::SinkSel0 | Max14819::PushPul); // Int Current Sink, 5 mA, PushPull, Channel Enable
    
	// PortB
	// Set all Interrupts
	shadowReg = IOLChip0->readRegister(Max14819::InterruptEn);
	IOLChip0->writeRegister(Max14819::InterruptEn, Max14819::StatusIntEn | Max14819::WURQIntEn | Max14819::TxErrIntEnB | Max14819::RxErrIntEnB | Max14819::RxDaRdyIntEnB | shadowReg);

	shadowReg = IOLChip1->readRegister(Max14819::InterruptEn);
	IOLChip1->writeRegister(Max14819::InterruptEn, Max14819::StatusIntEn | Max14819::WURQIntEn | Max14819::TxErrIntEnB | Max14819::RxErrIntEnB | Max14819::RxDaRdyIntEnB | shadowReg);

	// Enable LedRxRdy and RyError LED
	shadowReg = IOLChip0->readRegister(Max14819::LEDCtrl);
	IOLChip0->writeRegister(Max14819::LEDCtrl, Max14819::RxRdyEnB | Max14819::RxErrEnB | shadowReg);
	// Initialize the Channel A register
	IOLChip0->writeRegister(Max14819::LCnfgB, Max14819::LRT0 | Max14819::LBL0 | Max14819::LBL1 | Max14819::LClimDis | Max14819::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
	IOLChip0->writeRegister(Max14819::CQCfgB, Max14819::SinkSel0 | Max14819::PushPul); // Int Current Sink, 5 mA, PushPull, Channel Enable

	shadowReg = IOLChip1->readRegister(Max14819::LEDCtrl);
	IOLChip1->writeRegister(Max14819::LEDCtrl, Max14819::RxRdyEnB | Max14819::RxErrEnB | shadowReg);
	// Initialize the Channel A register
	IOLChip1->writeRegister(Max14819::LCnfgB, Max14819::LRT0 | Max14819::LBL0 | Max14819::LBL1 | Max14819::LClimDis | Max14819::LEn); // Enable current retry 0.4s,  disable currentlimiting, enable Current
	IOLChip1->writeRegister(Max14819::CQCfgB, Max14819::SinkSel0 | Max14819::PushPul); // Int Current Sink, 5 mA, PushPull, Channel Enable

    // Wait 0.2s for bootup of the device
	wait_for(Max14819::INIT_BOOTUP_DELAY);
}

void HardwareArduino::wait_for(uint32_t delay_ms)
{
    delay(delay_ms);
}

std::shared_ptr<openiolinklibrary::IOLMasterPort> HardwareArduino::getPort(uint8_t portnr)
{
	switch (portnr)
	{
	case 0:
		return PORT0;
		break;
	case 1:
		return PORT1;
		break;
	case 2:
		return PORT2;
		break;
	case 3:
		return PORT3;
		break;
	
	default:
		return nullptr;
		break;
	}
}

HardwareArduino::PIN_arduino::PIN_arduino(PinNames name, PinMode mode){
	this->init(name, mode);
}

HardwareArduino::PIN_arduino::~PIN_arduino(){
	IO_PinMode(pinname, PinMode::in);
}

void HardwareArduino::PIN_arduino::init(PinNames name, PinMode mode){
	pinname = name;
	IO_PinMode(name, mode);
}

void HardwareArduino::PIN_arduino::set(bool state){
	// High active
	if (state)
	{
		IO_Write(pinname, PIN_LOW);
	}
	else
	{
		IO_Write(pinname, PIN_HIGH);
	}
}

void HardwareArduino::PIN_arduino::IO_Write(PinNames pinname, uint8_t state)
{
    uint8_t pinnumber = get_pinnumber(pinname);
	digitalWrite(pinnumber, state);
}

void HardwareArduino::PIN_arduino::IO_PinMode(PinNames pinname, PinMode mode)
{
    uint8_t pinnumber = get_pinnumber(pinname);
	switch (mode) {
	case PinMode::out      : pinMode(pinnumber, OUTPUT); break;
	case PinMode::in_pullup: pinMode(pinnumber, INPUT_PULLUP); break;
	case PinMode::in       : pinMode(pinnumber, INPUT); break;
	}
}

void HardwareArduino::SPI_arduino::init(std::shared_ptr<PIN_arduino> cs_pin_)
{	
	cs_pin=cs_pin_;
}

HardwareArduino::SPI_arduino::SPI_arduino(std::shared_ptr<PIN_arduino> cs_pin_)
{
	this->init(cs_pin_);
}

void HardwareArduino::SPI_arduino::DataRW(uint8_t * data, uint8_t length)
{
	cs_pin->set(true);
    for(int i = 0; i<length; i++){
        data[i] = SPI.transfer(data[i]);
    }
	cs_pin->set(false);
}

void HardwareArduino::Serial_Write(char const * buf)
{
	Serial.print(buf);
	Serial.print("\n\r");
}

void HardwareArduino::Serial_Write(int number)
{
	Serial.print(number);
}

uint8_t HardwareArduino::PIN_arduino::get_pinnumber(PinNames pinname)
{
	switch (pinname) {
		case PinNames::port01CS:		return 10u;
		case PinNames::port23CS:		return 4u;
		case PinNames::port01IRQ:		return 5u;
		case PinNames::port23IRQ:		return 11u;
		case PinNames::port0DI:		return 55u;
		case PinNames::port1DI:		return 54u;
		case PinNames::port2DI:		return 14u;
		case PinNames::port3DI:		return 15u;

		case PinNames::port0LedGreen: return 2u;
		case PinNames::port0LedRed:	return 3u;
		case PinNames::port0LedRxErr:	return 61u;
		case PinNames::port0LedRxRdy:	return 60u;

		case PinNames::port1LedGreen: return 56u;
		case PinNames::port1LedRed:	return 57u;
		case PinNames::port1LedRxErr:	return 58u;
		case PinNames::port1LedRxRdy:	return 59u;

		case PinNames::port2LedGreen: return 6u;
		case PinNames::port2LedRed:	return 7u;
		case PinNames::port2LedRxErr:	return 9u;
		case PinNames::port2LedRxRdy:	return 8u;

		case PinNames::port3LedGreen: return 71u;
		case PinNames::port3LedRed:	return 70u;
		case PinNames::port3LedRxErr:	return 13u;
		case PinNames::port3LedRxRdy:	return 12u;
	}
	return uint8_t();
}

void HardwareArduino::SerialOut::print(char const * buf)
{
	printf("%s\n\r", buf);
}

void HardwareArduino::Wait_arduino::ms(uint32_t time_ms) 
{
	delay(time_ms);
}