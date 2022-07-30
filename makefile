CC=gcc
CFLAGS=-O2 -Wall 
TARGET=my_sort
SRC=./code/*.c

all: $(SRC)
	clear
	rm  -rf ./output/*.txt
	$(CC) $(CFLAGS) $(SRC) -o ./bin/$(TARGET) -pthread
	./bin/my_sort

