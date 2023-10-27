//
// Created by daniel on 23.10.23.
//

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

uint16_t program_counter = 0;
uint16_t index_register = 0;
uint16_t registers[16]; //TODO should be 8bit and rename to "v"

static uint8_t memory[4096];
static const uint16_t LAST_MEMORY_ADDR = 4095;

void init_memory() {
	program_counter = 0x200; // The address at which the ROM starts
	index_register = 0;

	for (int i = 0; i < sizeof(registers)/sizeof(registers[0]); i++) {
		registers[i] = 0;
	}

	for (int i = 0; i < sizeof(memory)/sizeof(memory[0]); i++) {
		memory[i] = 0;
	}
}

uint8_t memory_read(uint16_t address) {
	if (address > LAST_MEMORY_ADDR) {
		printf("Error: Tried reading invalid memory address\n");
		exit(EXIT_FAILURE);
	}

	return memory[address];
}

void memory_write(uint16_t address, uint8_t value) {
	if (address > LAST_MEMORY_ADDR) {
		printf("Error: Tried writing to invalid memory address\n");
		exit(EXIT_FAILURE);
	}

	memory[address] = value;
}
