//
// Created by daniel on 24.10.23.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

static uint16_t stack[16]; // Only used to store memory addresses
static int8_t stack_ptr;

void init_stack() {
	stack_ptr = -1; // Equals empty stack

	for (int i = 0; i < sizeof(stack)/sizeof(stack[0]); i++) {
		stack[i] = 0;
	}
}

void stack_push(uint8_t value) {
	stack_ptr++;

	if (stack_ptr > sizeof(stack) / sizeof(stack[0]) - 1) {
		printf("Error: Stack overflow\n");
		exit(EXIT_FAILURE);
	}
	stack[stack_ptr] = value;
}

uint16_t stack_pop() {
	uint16_t value = stack[stack_ptr];
	stack[stack_ptr] = 0;

	if (stack_ptr == -1) {
		printf("Error: Tried accessing empty stack\n");
		exit(EXIT_FAILURE);
	}
	stack_ptr--;

	return value;
}
