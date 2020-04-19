# macro tells which compiler to use
CC = g++

# macro says using c++11 standard
CFLAGS = -std=c++11 -c

# run "make all" to run shopping
all: shopping

# make the shopping sort program
shop: shopping.o
	$(CC) shopping.o -o bad

shopping.o:
	$(CC) $(CFLAGS) shopping.cpp


clean:
	rm *.o
	rm -f results.txt
	rm shopping