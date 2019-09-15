#include "HardwareRaspberry.h"
#include <stdio.h>
#include <unistd.h>

#include <iostream>				// Needed for File-IO
#include <fstream>				// Needed for File-IO

#include <wiringPi.h>

#include <fcntl.h>   			// Needed for SPI port
#include <sys/ioctl.h>			// Needed for SPI port
#include <linux/spi/spidev.h>	// Needed for SPI port

#include <wiringPiSPI.h>		// Needed for SPI communication
//int wiringPiSPIGetFd     (int channel) ;
//int wiringPiSPIDataRW    (int channel, unsigned char *data, int len) ;
//int wiringPiSPISetupMode (int channel, int speed, int mode) ;
//int wiringPiSPISetup     (int channel, int speed) ;





#define LOW 0
#define HIGH 1

HardwareRaspberry::HardwareRaspberry()
{
	// Init Wiring Pi
	wiringPiSetup();

	// Init SPI
	Serial_Write("Init_SPI starts");
	wiringPiSPISetup(0, 500000);
	wiringPiSPISetup(1, 500000);

	Serial_Write("Init_SPI finished");
	wait_for(1*1000);

	uint8_t buf[8];
	buf[0] = 14;
	buf[1] = 0;
	buf[2] = 78;
	buf[3] = 0;
	buf[4] = 14;
	buf[5] = 170;
	buf[6] = 78;
	buf[7] = 170;

	while(0){
		for(uint8_t i = 0; i<2; i++){ 
			SPI_Write(i, &buf[0], 2);
			SPI_Write(i, &buf[2], 2);
			buf[0] = 14;
			buf[1] = 0;
			buf[2] = 78;
			buf[3] = 0;
			buf[4] = 14;
			buf[5] = 170;
			buf[6] = 78;
			buf[7] = 170;
			wait_for(1*1000);
			SPI_Write(i, &buf[4], 2);
			SPI_Write(i, &buf[6], 2);
			wait_for(1*1000);
			buf[0] = 14;
			buf[1] = 0;
			buf[2] = 78;
			buf[3] = 0;
			buf[4] = 14;
			buf[5] = 170;
			buf[6] = 78;
			buf[7] = 170;
		}
	}
}


HardwareRaspberry::~HardwareRaspberry()
{
	//Deinit SPI
	// TODO
}

void HardwareRaspberry::IO_Write(uint8_t pinnumber, uint8_t state)
{
	switch (state) {
		case HIGH	: digitalWrite(pinnumber, HIGH); break;
		case LOW	: digitalWrite(pinnumber, LOW); break;
	}

}

void HardwareRaspberry::IO_PinMode(uint8_t pinnumber, PinMode mode)
{
	switch (mode) {
	case out: 
		pinMode(pinnumber, OUTPUT);
		break;
	case in_pullup: 
		pinMode(pinnumber, INPUT);
		pullUpDnControl(pinnumber, PUD_UP);
		break;
	case in:
		pinMode(pinnumber, INPUT);
		pullUpDnControl(pinnumber, PUD_OFF);
		break;
	}
}

void HardwareRaspberry::Serial_Write(char const * buf)
{
	printf("%s\n", buf);
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