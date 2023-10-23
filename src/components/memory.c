//
// Created by daniel on 23.10.23.
//

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

static u_int8_t memory[4096];
static const u_int16_t LAST_MEMORY_ADDR = 4095;

u_int8_t memory_read(u_int16_t address) {
	if (address > LAST_MEMORY_ADDR) {
		perror("Error: Tried reading invalid memory address\n");
		exit(EXIT_FAILURE);
	}

	return memory[address];
}

void memory_write(u_int16_t address, u_int8_t value) {
	if (address > LAST_MEMORY_ADDR) {
		perror("Error: Tried writing to invalid memory address\n");
		exit(EXIT_FAILURE);
	}

	memory[address] = value;
}
