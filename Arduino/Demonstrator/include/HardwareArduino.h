#pragma once
#include "HardwareBase.h"

class HardwareArduino :
	public HardwareBase
{
	

public:
	HardwareArduino();
	~HardwareArduino();

	virtual void begin();

	virtual void IO_Write(uint8_t pinnumber, uint8_t state);
	virtual void IO_PinMode(uint8_t pinnumber, PinMode mode); //pinMode

	virtual void Serial_Write(char const * buf);
	virtual void Serial_Write(int number);

	virtual void SPI_Write(uint8_t channel, uint8_t * data, uint8_t length);

	virtual void wait_for(uint32_t delay_ms);

private:

};