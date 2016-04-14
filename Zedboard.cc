#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <math.h>

#include "memmap_constants.h"
#include "Zedboard.h"

/** Constructor */
Zedboard::Zedboard() {
	calc_mem = 0;
	fd = open( "/dev/mem", O_RDWR);
	ptr = (char *) mmap( NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, gpio_address);
}

/** Destructor */
Zedboard::~Zedboard() {
	munmap(ptr, gpio_size);
	close(fd);
}

/** getptr */
char* Zedboard::getptr() {
	return ptr;
}

/** RegisterRead */
int Zedboard::RegisterRead(int offset) {
  return * (int *) (ptr + offset);
}

/** RegisterWrite */
void Zedboard::RegisterWrite(int offset, int value) {
  * (int *) (ptr + offset) = value;
}

/** SetSingleLedState */
void Zedboard::SetSingleLedState(int led_index, int state) {
  RegisterWrite(gpio_led1_offset + (led_index * 4), state);
}

/** SetLedStates */
void Zedboard::SetLedStates() {
	int i;
    for (i = 0; i < 8; i++) {
      SetSingleLedState(i, RegisterRead(gpio_sw1_offset + (i*4)));
    }
}

/** ReadNumber */
int Zedboard::ReadNumber() {
	int i;
	int result = 0;
	for (i = 0; i < 8; i++) {
		int switch_val = RegisterRead(gpio_sw1_offset + (i*4)) * (int) pow(2.0, (double) i);
		result = result + switch_val;
	}
	return result;
}

/** StoreNumber */
void Zedboard::StoreNumber(int value) {
	// Sanitize by cutting off any 8-bit overflow
	calc_mem = value % 256;
}

/** DisplayNumber */
void Zedboard::DisplayNumber() {
	int i;
	unsigned mask;
	for (i = 0; i < 8; i++) {
		int mask = ((1 << 1) - 1) << i;
		int single_bit = calc_mem & mask;
		SetSingleLedState(i, single_bit);
	}
}

/** Add */
int Zedboard::Add() {
	return calc_mem + ReadNumber();
}

/** Subtract */
int Zedboard::Subtract() {
	return calc_mem - ReadNumber();
}

/** Multiply */
int Zedboard::Multiply() {
	return calc_mem * ReadNumber();
}

/** Divide */
int Zedboard::Divide() {
	return calc_mem  / ReadNumber();
}

/** PushButtonGet */
int PushButtonGet() {
	if (RegisterRead(gpio_pbtnu_offet))
		return 1;
	if (RegisterRead(gpio_pbtnd_offset))
		return 2;
	if (RegisterRead(gpio_pbtnr_offset))
		return 3;
	if (RegisterRead(gpio_pbtnl_offset))
		return 4;
	if (RegisterRead(gpio_pbtnc_offset))
		return 5;
	return 0;
}