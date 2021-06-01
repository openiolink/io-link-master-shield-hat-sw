//!*****************************************************************************
//!  \file HardwareRaspberry.cpp
//!  
//!  \author 	Janik Lehmann (CrazyGecko) (xxthegeckoxx@gmail.com)
//!			  	based on the work of Markus Gafner (gnm7)
//!  
//!  \brief Generic Hardware Layer abstraction of a physical layer
//!  
//!  \date 2020-10-22
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

HardwareRaspberry::HardwareRaspberry()
{
	// TODO Fehlerabfrage
	// Init Wiring Pi
	wiringPiSetup();
	IO_Setup();

	// Init SPI
	printf("Init_SPI starts\n");
	spi0.init(0, std::make_shared<PIN_raspi>(CS_chip0));
	spi1.init(1, std::make_shared<PIN_raspi>(CS_chip1));
	printf("Init_SPI finished\n");
	wait_for(1*1000);

	// FIXME: IOLChip0, 1 als normale Member definieren, dann hier mit Initialisierer-Liste initialisiern
	// Gleiches für die Ports
	IOLChip0 = std::make_shared<Max14819>(Max14819(std::make_shared<SerialOut>(serialout), std::make_shared<SPI_raspi>(spi0), chip0Adresse_spi, std::make_shared<Wait_raspi>(wait_raspi)));
	IOLChip1 = std::make_shared<Max14819>(Max14819(std::make_shared<SerialOut>(serialout), std::make_shared<SPI_raspi>(spi1), chip1Adresse_spi, std::make_shared<Wait_raspi>(wait_raspi)));

	configure_Max14819();
	IOLChip0->initPorts();
	IOLChip1->initPorts();

	PORT0 = IOLChip0->getPort(Max14819::Max14819_Port::PortNr::PORTA);
	PORT1 = IOLChip0->getPort(Max14819::Max14819_Port::PortNr::PORTB);
	PORT2 = IOLChip1->getPort(Max14819::Max14819_Port::PortNr::PORTA);
	PORT3 = IOLChip1->getPort(Max14819::Max14819_Port::PortNr::PORTB);
}

HardwareRaspberry::~HardwareRaspberry()
{

}

void HardwareRaspberry::IO_Setup()
{
	// DRIVER0
	CS_chip0.init(PIN_raspi::PinNames::port01CS, PIN_raspi::PinMode::out);
	CS_chip0.set(false);
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
	
	redLED0.set(false);
	greenLED0.set(false);
	redLED1.set(false);
	greenLED1.set(false);
	
	// DRIVER1
	CS_chip1.init(PIN_raspi::PinNames::port23CS, PIN_raspi::PinMode::out);
	CS_chip0.set(false);
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
	
	redLED2.set(false);
	greenLED2.set(false);
	redLED3.set(false);
	greenLED3.set(false);
}

void HardwareRaspberry::configure_Max14819()
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

void HardwareRaspberry::Serial_Write(int number)
{
	printf("%d\n", number);
}

void HardwareRaspberry::SPI_Write(uint8_t channel, uint8_t * data, uint8_t length)
{
	//printf("SPI sending: %x, %x  ", data[0], data[1]);
	wiringPiSPIDataRW(channel, data, length);
	//printf("received %x,%x\n", data[0], data[1]);
}

void HardwareRaspberry::wait_for(uint32_t delay_ms)
{
	//printf("Sleep_in\n");
	usleep(delay_ms*1000);
	//printf("Sleep_out\n");
}

// TODO inline oder weg
std::shared_ptr<openiolinklibrary::IOLMasterPort> HardwareRaspberry::getPort(uint8_t portnr)
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

// FIXME: möglicherweise wird pinname nur hier verwendet, dann diesen nur hier als 
// Parameter verwenden, aber nicht abspeichern. Dafür die Pinnummer via get pinnumber
// schon in init() bestimmen und abspeichern.
HardwareRaspberry::PIN_raspi::PIN_raspi(PinNames name, PinMode mode){
	this->init(name, mode);
}

HardwareRaspberry::PIN_raspi::~PIN_raspi(){
	IO_PinMode(pinname, PinMode::in);
}

void HardwareRaspberry::PIN_raspi::init(PinNames name, PinMode mode){
	pinname = name;
	IO_PinMode(name, mode);
}

// Weiterführend: für Zeitoptimierung: zwei virtuelle Funktionen in Max14819::PIN, nämlich set() und clear()
// aber da wir vor allem LEDs an den Pins haben, ist das nicht so zeitkritisch 
void HardwareRaspberry::PIN_raspi::set(bool state){	// inline in hpp
	// High active
	if (state)
	{
		IO_Write(pinname, LOW);	// FIXME: Warum ein Attribut als Parameter übergeben?
	}
	else
	{
		IO_Write(pinname, HIGH);	// IO_Write unbedingt inline
	}
}

uint8_t HardwareRaspberry::PIN_raspi::get_pinnumber(PinNames pinname)	// inline in hpp und als constexpr-funtion
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

void HardwareRaspberry::PIN_raspi::IO_Write(PinNames pinname, uint8_t state)
{
	uint8_t pinnumber = get_pinnumber(pinname);
	switch (state) {
		case HIGH	: digitalWrite(pinnumber, HIGH); break;
		case LOW	: digitalWrite(pinnumber, LOW); break;
	}
}

void HardwareRaspberry::PIN_raspi::IO_PinMode(PinNames pinname, PinMode mode)
{
	uint8_t pinnumber = get_pinnumber(pinname);
	switch (mode) {
	case PinMode::out: 
		pinMode(pinnumber, OUTPUT);
		break;
	case PinMode::in_pullup: 
		pinMode(pinnumber, INPUT);
		pullUpDnControl(pinnumber, PUD_UP);
		break;
	case PinMode::in:
		pinMode(pinnumber, INPUT);
		pullUpDnControl(pinnumber, PUD_OFF);
		break;
}
}

void HardwareRaspberry::SPI_raspi::init(uint8_t channel_, std::shared_ptr<PIN_raspi> cs_pin_)
{	
	cs_pin=cs_pin_;
	if (channel_ > 1)
	{
		channel = 1;
	}
	else
	{
		channel = channel_;
	}
	wiringPiSPISetup(channel, spi_speed);
}

HardwareRaspberry::SPI_raspi::SPI_raspi(uint8_t channel_, std::shared_ptr<PIN_raspi> cs_pin_)
{
	this->init(channel_, cs_pin_);
}

void HardwareRaspberry::SPI_raspi::DataRW(uint8_t * data, uint8_t length)
{
	cs_pin->set(true);
	wiringPiSPIDataRW(channel, data, length);
	cs_pin->set(false);
}

void HardwareRaspberry::SerialOut::print(char const * buf)
{
	printf("%s\n", buf);
}

void HardwareRaspberry::Wait_raspi::ms(uint32_t time_ms) 
{
	usleep(time_ms*1000);
}