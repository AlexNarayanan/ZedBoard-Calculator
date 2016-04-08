#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <math.h>

#include "memmap_constants.h"

class ZedBoard {

	char *ptr;
	int fd;
		
	// Integer memory storage for the calculator
	int calc_mem; 

public: 

	/** Constructor */
	ZedBoard();
	
	/** Destructor */
	~Zedboard();
	
	/**
	 * Read a 4-byte value from the specified general-purpose I/O location.
	 *
	 * @param ptr Base address returned by 'mmap'.
	 * @param offset Offset where device is mapped.
	 * @return Value read.
	 */
	int Zedboard::RegisterRead(char *ptr, int offset);
	
	/**
	 * Write a 4-byte value at the specified general-purpose I/O location.
	 *
	 * @param ptr Base address returned by 'mmap'.
	 * @parem offset Offset where device is mapped.
	 * @param value Value to be written.
	 */
	void Zedboard::RegisterWrite(char *ptr, int offset, int value);	
	
	/** Set the state of the LED with the given index.
	 *
	 * @param ptr Base address for general-purpose I/O
	 * @parem led_index LED index between 0 and 7
	 * @param state Turn on (1) or off (0)
	 */
	void Zedboard::SetSingleLedState(void *ptr, int led_index, int state);
	
	/** Set the state of all LEDs to match the state of the switches
	 */
	void Zedboard::SetLedStates();
	
	/** Read in the number specified by the state of the switches
	 *  as an 8-bit integer. 
	 */
	 void Zedboard::ReadNumber();
	 
	 /** Add the number stored in memory to the number specified by the switches
	 */
	void Zedboard::Add();
	 
	/** Subtract the number specified by the switches from the number stored in memory
	 */
	void Zedboard::Subtract();
	  
	/** Multiple the number stored in memory by the number specified by the switches 
	 */
	void Zedboard::Multiply();

	/** Divide the number stored in memory by the number specified by the switches
	 */
	void Zedboard::Divide();	