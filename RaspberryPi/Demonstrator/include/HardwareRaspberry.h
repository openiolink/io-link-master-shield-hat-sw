#pragma once
#include <stdint.h>


namespace max14819 {
	// IO-Link Master Shield Arduino Due Pin Mapping
	constexpr uint8_t port01CS = 31u;			//SPI_CS0	(Pin24, output)
	constexpr uint8_t port23CS = 31u;			//SPI_CS1	(Pin26, output)
	constexpr uint8_t port01IRQ = 0u;			//P01_IRQ	(Pin11, input)
	constexpr uint8_t port23IRQ = 4u;			//P23_IRQ	(Pin16, input)
	constexpr uint8_t port0DI = 7u;				//P0_DI     (Pin 7, input)
	constexpr uint8_t port1DI = 15u;			//P1_DI     (Pin 8, input)
	constexpr uint8_t port2DI = 16u;			//P2_DI     (Pin 10, input)
	constexpr uint8_t port3DI = 30u;			//P3_DI     (Not avaiable)

	constexpr uint8_t port0LedGreen = 9u;		//P1_LED_GN	(Pin 5, output)
	constexpr uint8_t port0LedRed = 8u;			//P1_LED_RD	(Pin 3, output)
	constexpr uint8_t port0LedRxErr = 23u;		//P0_RX_ERR	(Pin33, input, pullup)
	constexpr uint8_t port0LedRxRdy = 24u;		//P0_RX_RDY (Pin35, input, pullup)	
	constexpr uint8_t port0RxError = port0LedRxErr;		
	constexpr uint8_t port0RxReady = port0LedRxRdy;		


	constexpr uint8_t port1LedGreen = 21u;		//P0_LED_GN	(Pin29, output)
	constexpr uint8_t port1LedRed = 22u;		//P0_LED_RD	(Pin31, output)
	constexpr uint8_t port1RxError = 2u;		//P1_RX_ERR	(Pin13, input, pullup)
	constexpr uint8_t port1RxReady = 3u;		//P1_RX_RDY (Pin15, input, pullup)	
	constexpr uint8_t port1LedRxErr = port1RxError;
	constexpr uint8_t port1LedRxRdy = port1RxReady;

	constexpr uint8_t port2LedGreen = 25u;		//P3_LED_GN	(Pin37, output)
	constexpr uint8_t port2LedRed = 1u;			//P3_LED_RD	(Pin12, output)
	constexpr uint8_t port2RxError = 27u;		//P2_RX_ERR	(Pin36, input, pullup)
	constexpr uint8_t port2RxReady = 26u;		//P2_RX_RDY (Pin32, input, pullup)	
	constexpr uint8_t port2LedRxErr = port2RxError;
	constexpr uint8_t port2LedRxRdy = port2RxReady;

	constexpr uint8_t port3LedGreen = 29u;		//P2_LED_GN	(Pin40, output)
	constexpr uint8_t port3LedRed = 5u;			//P2_LED_RD	(Pin18, output)
	constexpr uint8_t port3RxError = 6u;		//P3_RX_ERR	(Pin22, input, pullup)
	constexpr uint8_t port3RxReady = 28u;		//P3_RX_RDY (Pin38, input, pullup)	
	constexpr uint8_t port3LedRxErr = port3RxError;
	constexpr uint8_t port3LedRxRdy = port3RxReady;
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

};
