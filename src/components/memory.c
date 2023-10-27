//
// Created by daniel on 23.10.23.
//

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#define LAST_MEMORY_ADDR 4095

// TODO: think about renaming them to PC, I and V
uint16_t program_counter = 0;
uint16_t index_register = 0;
uint8_t registers[16];

static uint8_t memory[4096];

void init_memory() {
	program_counter = ROM_START_ADDR;
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
