CC=i686-elf-gcc
BIN=../bin

all: start.o kernel.o 
	$(CC) -ffreestanding -nostdlib -g -T linker.ld $(BIN)/start.o $(BIN)/kernel.o -o $(BIN)/kernel.elf -lgcc

kernel.o: kernel.c
	$(CC) -std=gnu99 -ffreestanding -g -c kernel.c -o $(BIN)/kernel.o

start.o: start.s
	$(CC) -std=gnu99 -ffreestanding -g -c start.s -o $(BIN)/start.o

clean:
	rm $(BIN)/*

.PHONY: all