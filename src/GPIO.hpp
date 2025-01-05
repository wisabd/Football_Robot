#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

enum PIN_DIRECTION{
	INPUT_PIN=0,
	OUTPUT_PIN=1
};

enum PIN_VALUE{
	LOW=0,
	HIGH=1
};


/****************************************************************
 * gpio_export
 ****************************************************************/
void gpio_export(unsigned int gpio)
{
    int fd, len, er;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if (fd < 0) {
		perror("gpio/export");
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    er = write(fd, buf, len);
    if (er < 0) {
		perror("fail to write");
    }
    close(fd);
}

/****************************************************************
 * gpio_unexport
 ****************************************************************/
void gpio_unexport(unsigned int gpio)
{
    int fd, len, er;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
    if (fd < 0) {
		perror("gpio/export");
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    er = write(fd, buf, len);
    if (er < 0) {
		perror("fail to write");
    }
    close(fd);
}

/****************************************************************
 * gpio_set_dir
 ****************************************************************/
void gpio_set_dir(unsigned int gpio, PIN_DIRECTION out_flag)
{
    int fd, er;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
		perror("gpio/direction");
    }

    if (out_flag == OUTPUT_PIN) {
		er = write(fd, "out", 4);
		if (er < 0) {
			perror("fail to write");
		}
    }
    else {
		er = write(fd, "in", 3);
		if (er < 0) {
			perror("fail to write");
		}
    }

    close(fd);
}

/****************************************************************
 * gpio_set_value
 ****************************************************************/
void gpio_set_value(unsigned int gpio, PIN_VALUE value)
{
    int fd, er;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
		perror("gpio/set-value");
    }

    if (value==LOW) {
	er = write(fd, "0", 2);
	if (er < 0) {
	    perror("fail to write");
	}
    }
    else {
		er = write(fd, "1", 2);
		if (er < 0) {
			perror("fail to write");
		}
    }
    close(fd);
}

/****************************************************************
 * gpio_get_value
 ****************************************************************/
//int gpio_get_value(unsigned int gpio, unsigned int *value)
int gpio_get_value(unsigned int gpio, bool& value)
{
    int fd, er;
    char buf[MAX_BUF];
    char ch;

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY);
    if (fd < 0) {
		perror("gpio/get-value");
		return fd;
    }

    er = read(fd, &ch, 1);
    if (er < 0) {
		perror("fail to read");
    }
    else {
		if (ch != '0') {
			value = false;
		} else {
			value = true;
		}
    }
    close(fd);
    return 0;
}

void ExportTouchSen(const unsigned int* touchGPIO, const int NUM_TOUCH) {
    //export five GPIOs for touch sensor input
    for (int i=0; i<NUM_TOUCH; i++) {
		gpio_export(touchGPIO[i]);				// Export touch sensors
		gpio_set_dir(touchGPIO[i], INPUT_PIN);  
    }
}
void UnexportTouchSen(const unsigned int* touchGPIO, const int NUM_TOUCH) {
    //unexport five GPIOs for touch sensor input
    for (int i=0; i<NUM_TOUCH; i++) {
	gpio_unexport(touchGPIO[i]);		// Export touch sensors
    }
}

