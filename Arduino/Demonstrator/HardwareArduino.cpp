#include "HardwareArduino.h"
#include "Arduino.h"
#include "SPI.h"




HardwareArduino::HardwareArduino()
{
	Serial.begin(115200);

	Serial.print("\nBeginne mit der Initialisierung\n");
	SPI.begin();
	SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
	delay(1000);
}


HardwareArduino::~HardwareArduino()
{
}

void HardwareArduino::IO_Write(uint8_t pinnumber, uint8_t state)
{
	digitalWrite(pinnumber, state);
}

void HardwareArduino::IO_PinMode(uint8_t pinnumber, PinMode mode)
{
	switch (mode) {
	case out      : pinMode(pinnumber, OUTPUT); break;
	case in_pullup: pinMode(pinnumber, INPUT_PULLUP); break;
	case in       : pinMode(pinnumber, INPUT); break;
	}
}

void HardwareArduino::Serial_Write(char * buf)
{
	Serial.println(buf);
}

void HardwareArduino::Serial_Write(int number)
{
	Serial.print(number);
}

uint8_t HardwareArduino::SPI_Write(uint8_t data)
{
	return SPI.transfer(data);
}

void HardwareArduino::wait_for(uint32_t delay_ms)
{
	delay(delay_ms);
}
