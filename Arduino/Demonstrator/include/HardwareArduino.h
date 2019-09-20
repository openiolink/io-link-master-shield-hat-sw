#pragma once
#include <stdint.h>
#include "WString.h"

namespace max14819 {
	// IO-Link Master Shield Arduino Due Pin Mapping
	constexpr uint8_t port01CS = 10u;
	constexpr uint8_t port23CS = 4u;
	constexpr uint8_t port01IRQ = 5u;
	constexpr uint8_t port23IRQ = 11u;
	constexpr uint8_t port0DI = 55u;
	constexpr uint8_t port1DI = 54u;
	constexpr uint8_t port2DI = 14u;
	constexpr uint8_t port3DI = 15u;

	constexpr uint8_t port0LedGreen = 2u;
	constexpr uint8_t port0LedRed = 3u;
	constexpr uint8_t port0RxError = 61u;
	constexpr uint8_t port0RxReady = 60u;
	constexpr uint8_t port0LedRxErr = 61u;
	constexpr uint8_t port0LedRxRdy = 60u;

	constexpr uint8_t port1LedGreen = 56u;
	constexpr uint8_t port1LedRed = 57u;
	constexpr uint8_t port1RxError = 58u;
	constexpr uint8_t port1RxReady = 59u;
	constexpr uint8_t port1LedRxErr = 58u;
	constexpr uint8_t port1LedRxRdy = 59u;

	constexpr uint8_t port2LedGreen = 6u;
	constexpr uint8_t port2LedRed = 7u;
	constexpr uint8_t port2RxError = 9u;
	constexpr uint8_t port2RxReady = 8u;
	constexpr uint8_t port2LedRxErr = 9u;
	constexpr uint8_t port2LedRxRdy = 8u;

	constexpr uint8_t port3LedGreen = 71u;
	constexpr uint8_t port3LedRed = 70u;
	constexpr uint8_t port3RxError = 13u;
	constexpr uint8_t port3RxReady = 12u;
	constexpr uint8_t port3LedRxErr = 13u;
	constexpr uint8_t port3LedRxRdy = 12u;

	constexpr uint8_t geckoSCK = 52u;
	constexpr uint8_t geckoMISO = 50u;
	constexpr uint8_t geckoMOSI = 53u;
}


class HardwareArduino
{
	

public:
	HardwareArduino();
	~HardwareArduino();

	void begin();

	enum PinMode { out, in_pullup, in };

	void IO_Write(uint8_t pinnumber, uint8_t state);
	void IO_PinMode(uint8_t pinnumber, PinMode mode); //pinMode

	static void Serial_Write(char const * buf);
	static void Serial_Write(int number);

	void SPI_Write(uint8_t channel, uint8_t * data, uint8_t length);

	static void wait_for(uint32_t delay_ms);

private:

};