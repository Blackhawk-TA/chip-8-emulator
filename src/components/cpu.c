//
// Created by daniel on 24.10.23.
//

#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "display.h"
#include "stack.h"
#include "keypad.h"
#include "timer.h"

static int8_t global_tmp = -1; // Can be used to store values over multiple instructions.

void cpu_cycle() {
	uint16_t instruction = fetch();
	decode_and_execute(instruction);
}

uint16_t fetch() {
	uint8_t instruction_left_part = memory_read(program_counter);
	uint8_t instruction_right_part = memory_read(program_counter + 1);

	uint16_t instruction = (instruction_left_part << 8) | instruction_right_part;
	return instruction;
}

void decode_and_execute(uint16_t instruction) {
	/*
	 * The instruction consists of 4 parts. The first one is the opcode.
	 * X: The second part. Used to look up one of the 16 registers (VX) from V0 through VF.
	 * Y: The third part. Also used to look up one of the 16 registers (VY) from V0 through VF.
	 * N: The fourth part. A 4-bit number.
	 * NN: The second byte (third and fourth parts). An 8-bit immediate number.
	 * NNN: The second, third and fourth parts. A 12-bit immediate memory address.
	 */
	uint16_t opcode = (instruction & 0xF000) >> 12;
	uint16_t x = (instruction & 0x0F00) >> 8;
	uint16_t y = (instruction & 0x00F0) >> 4;
	uint16_t n = instruction & 0x000F;
	uint16_t nn = instruction & 0x00FF;
	uint16_t nnn = instruction & 0x0FFF;
	uint8_t tmp; // Can be used to store a value for a single instruction

	switch (opcode) {
		case 0x0:
			switch (instruction) {
				case 0x00E0: // Clear display
					clear_display();
					program_counter += 2;
					break;
				case 0x00EE: // Subroutine return
					program_counter = stack_pop();
					break;
				default:
					unknown_instruction(opcode);
			}
			break;
		case 0x1: // 1NNN: Jump, no PC increment
			program_counter = nnn;
			break;
		case 0x2: // 2NNN: Jump to subroutine
			stack_push(program_counter + 2); // Increment by 2, so it does not get stuck on the Jump instruction
			program_counter = nnn;
			break;
		case 0x3: // 3XNN: Skips one instruction if VX equals NN
			if (registers[x] == nn) {
				program_counter += 2;
			}
			program_counter += 2;
			break;
		case 0x4: // 4XNN: Skips one instruction if VX does not equal NN
			if (registers[x] != nn) {
				program_counter += 2;
			}
			program_counter += 2;
			break;
		case 0x5: // 5XY0: Skips if VX and VY are equal
			if (registers[x] == registers[y]) {
				program_counter += 2;
			}
			program_counter += 2;
			break;
		case 0x6: // 6XNN: Set register VX to value NN
			registers[x] = nn;
			program_counter += 2;
			break;
		case 0x7: // 7XNN: Adds NN to register VX, ignores overflows
			registers[x] += nn;
			program_counter += 2;
			break;
		case 0x8: // Logical operators
			switch (n) {
				case 0x0: // 8XY0: Set VX to value of VY
					registers[x] = registers[y];
					registers[0xF] = 0;
					program_counter += 2;
					break;
				case 0x1: // 8XY1: Binary OR
					registers[x] |= registers[y];
					registers[0xF] = 0;
					program_counter += 2;
					break;
				case 0x2: // 8XY2: Binary AND
					registers[x] &= registers[y];
					registers[0xF] = 0;
					program_counter += 2;
					break;
				case 0x3: // 8XY3: Binary XOR
					registers[x] ^= registers[y];
					registers[0xF] = 0;
					program_counter += 2;
					break;
				case 0x4: // 8XY4: Add VX is set to VX + VY, affects carry flag
					tmp = registers[x] + registers[y] > 255; // Use tmp var to prevent VF from being overwritten by result if VX = VF
					registers[x] += registers[y];
					registers[0xF] = tmp; // Set flag register to 1 on 8 bit overflow
					program_counter += 2;
					break;
				case 0x5: // 8XY5: Subtract sets VX to result of VX - VY
					tmp = registers[x] >= registers[y];
					registers[x] -= registers[y];
					registers[0xF] = tmp;
					program_counter += 2;
					break;
				case 0x6: // 8XY6: Shift 1 bit right
					registers[x] = registers[y];
					tmp = registers[x] & 0b1; // Set the bit that was shifted out to carry flag
					registers[x] >>= 1;
					registers[0xF] = tmp;
					program_counter += 2;
					break;
				case 0x7: // 8XY7: Subtract sets VX to result of VY - VX
					tmp = registers[y] >= registers[x];
					registers[x] = registers[y] - registers[x];
					registers[0xF] = tmp;
					program_counter += 2;
					break;
				case 0xE: // 8XYE: Shift 1 bit left
					registers[x] = registers[y];
					tmp = (registers[x] >> 7) & 0b1; // Set the bit that was shifted out to carry flag
					registers[x] <<= 1;
					registers[0xF] = tmp;
					program_counter += 2;
					break;
				default:
					unknown_instruction(instruction);
			}
			break;
		case 0x9: // 9XY0: Skips if VX and VY are not equal
			if (registers[x] != registers[y]) {
				program_counter += 2;
			}
			program_counter += 2;
			break;
		case 0xA: // ANNN: Sets index register to NNN
			index_register = nnn;
			program_counter += 2;
			break;
		case 0xB: // BNNN: Jump with offset
			program_counter = nnn + registers[0x0]; // TODO: Might cause problems
			break;
		case 0xC: // CXNN: Creates random number and binary ANDs it with value nn
			registers[x] = (rand() % 256) & nn;
			program_counter += 2;
			break;
		case 0xD: // DXYN: Draw n pixels at x, y
			draw(registers[x] % WIDTH, registers[y] % HEIGHT, n);
			program_counter += 2;
			break;
		case 0xE:
			switch (nn) {
				case 0x9E: // EX9E: Skip one instruction if key corresponding to value in VX is pressed
					if (is_key_pressed(registers[x])) {
						program_counter += 2;
					}
					program_counter += 2;
					break;
				case 0xA1: // EXA1: Skip one instruction if key corresponding to value in VX is not pressed
					if (!is_key_pressed(registers[x])) {
						program_counter += 2;
					}
					program_counter += 2;
					break;
				default:
					unknown_instruction(instruction);
			}
			break;
		case 0xF:
			switch (nn) {
				case 0x07: // FX07: Sets VX to current value of delay timer
					registers[x] = delay_timer;
					program_counter += 2;
					break;
				case 0x15: // FX15: Sets delay timer to value in VX
					delay_timer = registers[x];
					program_counter += 2;
					break;
				case 0x18: // FX18: Sets sound timer to value in VX
					sound_timer = registers[x];
					program_counter += 2;
					break;
				case 0x1E: // FX1E: Adds value of VF to index register I
					// Writing to VF is not part of original COSMAC VIP, however some games rely on it, so it is implemented.
					tmp = index_register + registers[x] > 0xFFF;
					index_register += registers[x];
					registers[0xF] = tmp;
					program_counter += 2;
					break;
				case 0x0A: // FX0A: Wait until a key is pressed and released. It writes the pressed key to VX
					handle_get_pressed(x);
					break;
				case 0x29: // FX29: Font character
					index_register = FONT_START_ADDR + FONT_BYTES_PER_CHAR * (registers[x] & 0x0F); // One char consists of 5 bytes
					program_counter += 2;
					break;
				case 0x33: // FX33: Binary-coded decimal conversion
					memory_write(index_register, (registers[x] / 100) % 10);
					memory_write(index_register + 1, (registers[x] / 10) % 10);
					memory_write(index_register + 2, registers[x] % 10);
					program_counter += 2;
					break;
				case 0x55: // FX55: Store memory
					for (uint16_t i = 0; i <= x; i++) {
						memory_write(index_register + i, registers[i]);
					}
					index_register = index_register + x + 1;
					program_counter += 2;
					break;
				case 0x65: // FX65: Load memory
					for (uint16_t i = 0; i <= x; i++) {
						registers[i] = memory_read(index_register + i);
					}
					index_register = index_register + x + 1;
					program_counter += 2;
					break;
				case 0x75: // These instructions are added but not implemented, so the sc_test can be run
				case 0x85:
					program_counter += 2;
					break;
				default:
					unknown_instruction(instruction);
			}
			break;
		default:
			unknown_instruction(opcode);
	}
}

void unknown_instruction(uint16_t instruction) {
	printf("Error: Unknown instruction '0x%04x'\n", instruction);
	exit(EXIT_FAILURE);
}

void handle_get_pressed(uint8_t x) {
	int8_t pressed_key = get_pressed_key();

	if (pressed_key != -1) { // A key was pressed, store it for next instruction to wait for release
		global_tmp = pressed_key;
	} else if (global_tmp != -1 && is_key_released(global_tmp)) { // global tmp is set to a key and it was released
		registers[x] = global_tmp;
		global_tmp = -1; // Reset global tmp variable
		program_counter += 2;
	}
}
