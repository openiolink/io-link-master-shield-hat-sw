#include "HardwareRaspberry.h"
#include <stdio.h>
#include <unistd.h>

#include <iostream>				// Needed for File-IO
#include <fstream>				// Needed for File-IO

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
	// Export GPIO's for use
	export_pin(max14819::port0LedGreen);
	export_pin(max14819::port0LedRed);
	export_pin(max14819::port0LedRxErr);
	export_pin(max14819::port0LedRxRdy);

	// Export CE0/CE1 for SPI
	//export_pin(max14819::port01CS);
	//export_pin(max14819::port23CS);

	// Init SPI
	Serial_Write("Init_SPI starts");
	wiringPiSPISetup(0, 500000);
	wiringPiSPISetup(1, 500000);

	Serial_Write("Init_SPI semi");
	init_spi();
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
		for(int i = 0; i<2; i++){ 
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
	unexport_pin(max14819::port0LedGreen);
	unexport_pin(max14819::port0LedRed);
	unexport_pin(max14819::port0LedRxErr);
	unexport_pin(max14819::port0LedRxRdy);

	//Deinit SPI
	// TODO
}

void HardwareRaspberry::IO_Write(uint8_t pinnumber, uint8_t state)
{
	switch (state) {
		case HIGH	: set_output_level_high(pinnumber, true); break;
		case LOW	: set_output_level_high(pinnumber, false); break;
	}

}

void HardwareRaspberry::IO_PinMode(uint8_t pinnumber, PinMode mode)
{
	switch (mode) {
	case out      : set_pin_direction_output(pinnumber, true); break;
	case in_pullup: set_pin_direction_output(pinnumber, false); break;
	case in       : set_pin_direction_output(pinnumber, false); break;
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

void HardwareRaspberry::init_spi(){
	static const char *device = "/dev/spidev0.0";
	static uint8_t mode;
	static uint8_t bits = 8;
	static uint32_t speed = 500000;
	static uint16_t delay;
	int ret, fd;

	// Open device
	if ((fd = open(device, O_RDWR)) < 0)
	{
		perror("Error Opening Device");
		exit(1);
	}
	// Set mode 
	/*ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret < 0)
	{
		perror("Error setting SPI-Mode");
		exit(1);
	}*/

	// Get mode
	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret < 0)
	{
		perror("Error getting SPI-Mode");
		exit(1);
	}

	// Set byte-length
	/*ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret < 0)
	{
		perror("Error setting byte length");
		exit(1);
	}*/

	// Get byte-length
	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret < 0)
	{
		perror("Error getting byte length");
		exit(1);
	}

	// Set bitrate
	/*ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret < 0)
	{
		perror("Error setting speed");
		exit(1);
	}*/
	
	// Get bitrate
	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret < 0)
	{
		perror("Error getting speed");
		exit(1);
	}

	/* Output */
	printf("SPI-Device.: %s\n", device);
	printf("SPI-Mode...: %d\n", mode);
	printf("Byte Length: %d\n", bits);
	printf("Batrate....: %d Hz (%d kHz)\n", speed, speed/1000);
}

void HardwareRaspberry::export_pin(unsigned int pin)
{
	std::ofstream file;
	file.open ("/sys/class/gpio/export");
	file << pin;
	file.close();
}

void HardwareRaspberry::unexport_pin(unsigned int pin)
{
	std::ofstream file;
	file.open ("/sys/class/gpio/unexport");
	file << pin;
	file.close();
}

void HardwareRaspberry::set_pin_direction_output(unsigned int pin, bool state)
{
	std::ofstream file;
	char buf[256];
	sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
	switch (state) {
		case true  	: file << "out"; break;
		case false	: file << "in"; break;
	}
	file.close();
}

void HardwareRaspberry::set_output_level_high(unsigned int pin, bool state)
{
	std::ofstream file;
	char buf[256];
	sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
	switch (state) {
		case true  	: file << "1"; break;
		case false	: file << "0"; break;
	}
	file.close();
}