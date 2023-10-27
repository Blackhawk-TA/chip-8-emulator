//
// Created by daniel on 24.10.23.
//

#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "display.h"
#include "stack.h"

uint32_t CLOCK_SPEED_HZ = 1000000; // 1 MHz //TODO change, so it is variable.

//TODO: It should handle around 700 instructions (cpu cycles) per second
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
			stack_push(program_counter);
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
					program_counter +=2;
					break;
				case 0x1: // 8XY1: Binary OR
					registers[x] |= registers[y];
					program_counter += 2;
					break;
				case 0x2: // 8XY2: Binary AND
					registers[x] &= registers[y];
					program_counter += 2;
					break;
				case 0x3: // 8XY3: Binary XOR
					registers[x] ^= registers[y];
					program_counter += 2;
					break;
				case 0x4: // 8XY4: Add VX is set to VX + VY, affects carry flag
					if (registers[x] + registers[y] > 255) {
						registers[0xF] = 1; // Set flag register to 1 on 8 bit overflow
					} else {
						registers[0xF] = 0; // Set flag register to 0 on no overflow
					}
					registers[x] += registers[y];
					program_counter += 2;
					break;
				case 0x5: // 8XY5: Subtract sets VX to result of VX - VY
					if (registers[x] > registers[y]) { // TODO: Not sure if implemented correctly, what about == ?
						registers[0XF] = 1;
					} else if (registers[x] < registers[y]) {
						registers[0XF] = 0;
					}
					registers[x] -= registers[y];
					program_counter += 2;
					break;
				case 0x6: // 8XY6: Shift 1 bit right
					registers[x] = registers[y]; // TODO: Might cause problems
					registers[0xF] = registers[x] & 0b1; // Set the bit that was shifted out to carry flag
					registers[x] >>= 1;
					break;
				case 0x7: // 8XY7: Subtract sets VX to result of VY - VX
					if (registers[y] > registers[x]) { // TODO: Not sure if implemented correctly, what about == ?
						registers[0XF] = 1;
					} else if (registers[y] < registers[x]) {
						registers[0XF] = 0;
					}
					registers[x] = registers[y] - registers[x];
					program_counter += 2;
					break;
				case 0xE: // 8XYE: Shift 1 bit left
					registers[x] = registers[y]; // TODO: Might cause problems
					registers[0xF] = (registers[x] >> 7) & 0b1; // Set the bit that was shifted out to carry flag
					registers[x] <<= 1;
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
			break;
		case 0xF:
			break;
		default:
			unknown_instruction(opcode);
	}
}

void unknown_instruction(uint16_t instruction) {
	printf("Error: Unknown instruction '0x%04x'\n", instruction);
	exit(EXIT_FAILURE);
}
