#pragma once
#include <stdint.h>


namespace max14819 {
	// IO-Link Master Shield Arduino Due Pin Mapping
	constexpr uint8_t port01CS = 8u;			//SPI_CS0	(Pin24, output)
	constexpr uint8_t port23CS = 7u;			//SPI_CS1	(Pin26, output)
	constexpr uint8_t port01IRQ = 17u;			//P01_IRQ	(Pin11, input)
	constexpr uint8_t port23IRQ = 11u;
	constexpr uint8_t port0DI = 4u;				//P0_DI     (Pin 7, input)
	constexpr uint8_t port1DI = 14u;			//P1_DI     (Pin 8, input)
	constexpr uint8_t port2DI = 14u;
	constexpr uint8_t port3DI = 15u;

	constexpr uint8_t port0LedGreen = 3u;		//P1_LED_GN	(Pin5, output)
	constexpr uint8_t port0LedRed = 2u;			//P1_LED_RD	(Pin3, output)
	constexpr uint8_t port0LedRxErr = 13u;		//P0_RX_ERR	(Pin33, input, pullup)
	constexpr uint8_t port0LedRxRdy = 19u;		//P0_RX_RDY (Pin35, input, pullup)	
	constexpr uint8_t port0RxError = port0LedRxErr;		
	constexpr uint8_t port0RxReady = port0LedRxRdy;		


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
}


class HardwareRaspberry
{
	

public:
	HardwareRaspberry();
	~HardwareRaspberry();

	enum PinMode { out, in_pullup, in };

	void IO_Write(uint8_t pinnumber, uint8_t state);
	void IO_PinMode(uint8_t pinnumber, PinMode mode); //pinMode

	static void Serial_Write(char const * buf);
	static void Serial_Write(int number);

	void SPI_Write(uint8_t channel, uint8_t * data, uint8_t length);

	static void wait_for(uint32_t delay_ms);

private:
	void init_spi();
	void export_pin(unsigned int pin);
	void unexport_pin(unsigned int pin);
	void set_pin_direction_output(unsigned int pin, bool state);
	void set_output_level_high(unsigned int pin, bool state);

};
