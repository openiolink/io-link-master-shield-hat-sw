#pragma once
#include <cstdint>

class HardwareBase
{


public:
	HardwareBase();
	~HardwareBase();

	enum PinMode { out, in_pullup, in };

	enum PinNames {port01CS, port23CS, port01IRQ, port23IRQ, port0DI, port1DI, port2DI, port3DI,	
	port0LedGreen, port0LedRed, port0LedRxErr, port0LedRxRdy,
	port1LedGreen, port1LedRed, port1LedRxErr, port1LedRxRdy,
	port2LedGreen, port2LedRed, port2LedRxErr, port2LedRxRdy,
	port3LedGreen, port3LedRed, port3LedRxErr, port3LedRxRdy
	};

	virtual void begin() = 0;	

	virtual void IO_Write(PinNames pinnumber, uint8_t state) = 0;
	virtual void IO_PinMode(PinNames pinnumber, PinMode mode) = 0; //pinMode

	virtual void Serial_Write(char const * buf) = 0;
	virtual void Serial_Write(int number) = 0;

	virtual void SPI_Write(uint8_t channel, uint8_t * data, uint8_t length) = 0;

	virtual void wait_for(uint32_t delay_ms) = 0;

private:

};