//
// Created by daniel on 24.10.23.
//

#include <stdio.h>
#include "stack.h"

static u_int16_t stack[16]; // Only used to store memory addresses
static int8_t stack_ptr;

void init_stack() {
	stack_ptr = -1; // Equals empty stack

	for (int i = 0; i < sizeof(stack)/sizeof(stack[0]); i++) {
		stack[i] = 0;
	}
}

void stack_push(u_int8_t value) {
	stack_ptr++;

	if (stack_ptr > sizeof(stack) / sizeof(stack[0]) - 1) {
		printf("Error: Stack overflow");
		exit(EXIT_FAILURE);
	}
	stack[stack_ptr] = value;
}

u_int16_t stack_pop() {
	u_int16_t value = stack[stack_ptr];
	stack[stack_ptr] = 0;

	if (stack_ptr == -1) {
		printf("Error: Tried accessing empty stack");
		exit(EXIT_FAILURE);
	}
	stack_ptr--;

	return value;
}
