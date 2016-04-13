main: main.o Zedboard.o
	g++ main.o Zedboard.o -o main

main.o: main.cc Zedboard.cc Zedboard.h
	g++ -c main.cc

zedboard.o: Zedboard.cc Zedboard.h memmap_constants.h
	g++ -c Zedboard.cc

clean:
	rm -r -f *o 