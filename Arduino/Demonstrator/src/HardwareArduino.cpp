#include "../include/HardwareArduino.h"
#include <Arduino.h>
#include <SPI.h>
#include <stdio.h>




HardwareArduino::HardwareArduino()
{
    // Define all SPI signals for the Geckoboard as inputs. if not, MOSI cant be thrown to 0V
    IO_PinMode(50, in);
    IO_PinMode(52, in);
    IO_PinMode(53, in);
}


HardwareArduino::~HardwareArduino()
{
}


void HardwareArduino::begin(){

	Serial.begin(115200);

	Serial.print("\nBeginne mit der Initialisierung\n");

	SPI.begin();
	SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
	delay(1000);

	Serial_Write("Init_SPI finished");
	wait_for(1*1000);
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

void HardwareArduino::Serial_Write(char const * buf)
{
	Serial.println(buf);
}

void HardwareArduino::Serial_Write(int number)
{
	Serial.print(number);
}

void HardwareArduino::SPI_Write(uint8_t channel, uint8_t * data, uint8_t length)
{
    switch(channel){
        case 0:
            // Enable chipselect -> output high (low-active)
            IO_Write(max14819::port01CS, LOW);
            break;
        case 1:
            // Enable chipselect -> output high (low-active)
            IO_Write(max14819::port23CS, LOW);
            break;
    }


    for(int i = 0; i<length; i++){
        data[i] = SPI.transfer(data[i]);
    }

    // Disable chipselect -> output high (low-active)
    IO_Write(max14819::port01CS, HIGH);
    IO_Write(max14819::port23CS, HIGH);
    

}

void HardwareArduino::wait_for(uint32_t delay_ms)
{
    delay(delay_ms);
}