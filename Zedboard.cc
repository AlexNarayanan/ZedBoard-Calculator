#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <math.h>

#include "memmap_constants.h"
#include "zedboard.h"


/** Constructor */
Zedboard::Zedboard() {
	fd = open( "/dev/mem", O_RDWR);
	ptr = (char *) mmap( NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, gpio_address);
}

/** Destructor */
Zedboard::~Zedboard() {
	munmap(ptr, gpio_size);
	close(fd);
}

/** RegisterRead */
int Zedboard::RegisterRead(char *ptr, int offset) {
  return * (int *) (ptr + offset);
}

/** RegisterWrite */
void Zedboard::RegisterWrite(char *ptr, int offset, int value) {
  * (int *) (ptr + offset) = value;
}

/** SetSingleLedState */
void Zedboard::SetSingleLedState(void *ptr, int led_index, int state) {
  RegisterWrite(ptr, gpio_led1_offset + (led_index * 4), state);
}

/** SetLedStates */
void Zedboard::SetLedStates() {
	int i;
    for (i = 0; i < 8; i++) {
      SetLedState(this.ptr, i, RegisterRead(ptr, gpio_sw1_offset + (i*4)));
    }
}

/** ReadNumber */
int Zedboard::ReadNumber() {
	int i;
	int result = 0;
	for (i = 0; i < 8; i++) {
		int switch_val = RegisterRead(ptr, gpio_sw1_offset + (i*4)) * (int) pow(2.0, (double) i);
		result = result + switch_val;
	}
	return result;
}

/** Add */
int Zedboard::Add() {
	return this.calc_mem + ReadNumber();
}

/** Subtract */
int Zedboard::Subtract() {
	return this.calc_mem - ReadNumber();
}

/** Multiply */
int Zedboard::Multiply() {
	return this.calc_mem * ReadNumber();
}

/** Divide */
int Zedboard::Divide() {
	return this.calc_mem  / ReadNumber();
}