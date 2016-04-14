#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

#include "memmap_constants.h"

int main() {
	
	Zedboard zedboard;
	// Check that memory mapped correctly
	if (zedboard.getptr() == MAP_FAILED) {
		perror("Mapping I/O memor failed - Did you run with sudo?\n");
		return -1;
	}
	int numberRead;
	int buttonstate;
	
	// main loop
	while (1) {
		buttonstate = zb.PushButtonGet();
		switch (buttonstate) {
			// No button pressed - Do Nothing
			case 0:
				break;
			// Up button pressed - Multiply
			case 1:
				numberRead = zb.ReadNumber();
				zb.StoreNumber(zb.Multiply(numberRead));
				zb.DisplayNumber();
				break;
			// Down button pressed - Divide
			case 2:
				numberRead = zb.ReadNumber();
				zb.StoreNumber(zb.Divide(numberRead));
				zb.DisplayNumber();
				break;
			// Right button pressed - Add
			case 3:
				numberRead = zb.ReadNumber();
				zb.StoreNumber(zb.Add(numberRead));
				zb.DisplayNumber();
				break;
			// Left button pressed - Divide
			case 4:
				numberRead = zb.ReadNumber();
				zb.StoreNumber(zb.Divide(numberRead));
				zb.DisplayNumber();
				break;
			// Center button pressed - Store Number
			case 5:
				numberRead = zb.ReadNumber();
				zb.StoreNumber(numberRead);
				zb.DisplayNumber();
				break;
				
		}
	}
}