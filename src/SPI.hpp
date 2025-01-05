/* Copyright (c) 2013 Owen McAree
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Serial Peripheral Interface (SPI) bus Class
 *	This class allows you to take control of devices on the SPI bus from Linux
 *	It has been developed and tested on the BeagleBone Black but should work on
 *	any Linux system with spidev support (e.g. Raspberry Pi)
 *
 *	Usage is simple...
 *	To create an instance, point the constructor at your SPI bus
 *		SPI *myBus = new SPI("/dev/spidev1.0");
 *
 *	Set the speed of the bus (or leave it at the 100kHz default)
 *		myBus->setMaxSpeedHz(1000000);
 *
 *	Transfer some data
 *		uint8_t tx[] = {0x55, 0x00};
 *		uint8_t rx[] = {0x00, 0x00};
 *		myBus->transfer(tx, rx, 2);
 *	Note that tx and rx arrays must be the same size
 *	(the size is passed as the 3rd parameter to 'transfer')
 *
 *	Close the bus
 *		myBus->close();
 */
#pragma once

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>


int16_t combine(uint8_t upper, uint8_t lower)
{
    return ((uint16_t)upper) << 8 | lower;
}

class SPI {
public:
	SPI(const char *device) {
		this->device = device;
		this->fd = open(this->device, O_RDWR);
		if (fd < 0) {
			perror("Unable to open SPI device\n");
		}
		this->setMode(0);
		this->setBitsPerWord(8);
		this->setMaxSpeedHz(100000);
		this->setDelayUsecs(0);
	}

	~SPI() {
		close();
	}

	// Set the mode of the bus (see linux/spi/spidev.h)
	void setMode(uint8_t mode) {
		int ret = ioctl(this->fd, SPI_IOC_WR_MODE, &mode);
		if (ret == -1)
			perror("Unable to set SPI mode");

		ret = ioctl(this->fd, SPI_IOC_RD_MODE, &this->mode);
		if (ret == -1)
			perror("Unable to get SPI mode");
	}

	// Get the mode of the bus
	uint8_t getMode() {
		return this->mode;
	}

	// Set the number of bits per word
	void setBitsPerWord(uint8_t bits) {
		int ret = ioctl(this->fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
		if (ret == -1)
			perror("Unable to set bits per word");

		ret = ioctl(this->fd, SPI_IOC_RD_BITS_PER_WORD, &this->bits);
		if (ret == -1)
			perror("Unable to get bits per word");
	}

	// Get the number of bits per word
	uint8_t getBitsPerWord() {
		return this->bits;
	}

	// Set the bus clock speed
	void setMaxSpeedHz(uint32_t speed) {
		int ret = ioctl(this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
		if (ret == -1)
			perror("Unable to set max speed Hz");

		ret = ioctl(this->fd, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed);
		if (ret == -1)
			perror("Unable to get max speed Hz");
	}

	// Get the bus clock speed
	uint32_t getMaxSpeedHz() {
		return this->speed;
	}

	// Set the bus delay
	void setDelayUsecs(uint16_t delay) {
		this->delay = delay;
	}

	// Get the bus delay
	uint16_t getDelayUsecs() {
		return this->delay;
	}

	// Transfer some data
	bool transfer(uint8_t *tx, uint8_t *rx, int length) {
	   struct spi_ioc_transfer tr;
	   
	   tr.tx_buf = (unsigned long)tx;	//tx and rx MUST be the same length!
	   tr.rx_buf = (unsigned long)rx;
	   tr.len = length;
	   tr.delay_usecs = this->delay;
	   tr.speed_hz = this->speed;       
	   tr.bits_per_word = this->bits;

	   int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	   if (ret == 1) {
		  perror("Unable to send spi message");
		  return false;
		}
		return true;
	}

	// Close the bus
	void close() {
	   ::close(this->fd);
	}
private:
	const char *device;
	int fd;
	uint8_t mode;
	uint8_t bits;
	uint32_t speed;
	uint16_t delay;
};


