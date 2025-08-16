CC=gcc
INC_DIR=-I./include
LIB_DIR=
LIB=
CFLAGS=-Wall -O0

build:
	gcc ./src/main.c ./src/lz77.c ./src/file.c -I./include/

main: lz77.o file.o
	$(CC) $(CFLAGS) -o ./build/main src/main.c build/lz77.o build/file.o $(INC_DIR)

file.o:
	$(CC) $(CFLAGS) -o ./build/file src/file.c $(INC_DIR)

lz77.o:
	$(CC) $(CFLAGS) -o ./build/lz77 src/lz77.c $(INC_DIR)

run:
	./build/main

clean:
	rm -rf ./build/*
