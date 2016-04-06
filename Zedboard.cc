#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

#include "memmap_constants.h"
#include "zedboard.h"


/** Constructor */
Zedboard::Zedboard() {
	fd = open( "/dev/mem", O_RDWR);
	ptr = (char *) mmap( NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, gpio_address);
}

/** Destructor */
Zedboard::~ZedBoard() {
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

/** Set the state of all LEDs 
 *
 */
void Zedboard::SetLedStates() {
	int i;
    for (i = 0; i < 8; i++) {
      SetLedState(this.ptr, i, RegisterRead(ptr, gpio_sw1_offset + (i*4)));
    }
}