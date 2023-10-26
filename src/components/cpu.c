//
// Created by daniel on 24.10.23.
//

#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "display.h"

uint32_t CLOCK_SPEED_HZ = 1000000; // 1 MHz
uint16_t registers[16] = {}; //The CPU registers V0 - VF
uint16_t carry_flag_register = 0;

//TODO: It should handle around 700 instructions (cpu cycles) per second
void cpu_cycle() {
	uint16_t instruction = fetch();
	decode_and_execute(instruction);
}

uint16_t fetch() {
	uint8_t instruction_left_part = memory_read(program_counter++);
	uint8_t instruction_right_part = memory_read(program_counter++);

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
	uint16_t op_code = (instruction & 0xF000) >> 12;
	uint16_t x = (instruction & 0x0F00) >> 8;
	uint16_t y = (instruction & 0x00F0) >> 4;
	uint16_t n = instruction & 0x000F;
	uint16_t nn = instruction & 0x00FF;
	uint16_t nnn = instruction & 0x0FFF;

	switch (op_code) {
		case 0x0:
			switch (instruction) {
				case 0x00E0: // Clear display
					clear_display();
					break;
				case 0x00EE: // Subroutine return
					break;
				default:
					printf("Error: Unknown instruction identifier");
					exit(EXIT_FAILURE);
			}
			break;
		case 0x1: // 1NNN: Jump
			program_counter = nnn;
			break;
		case 0x2:
			break;
		case 0x3:
			break;
		case 0x4:
			break;
		case 0x5:
			break;
		case 0x6: // 6XNN: Set register VX to value NN
			registers[x] = nn;
			break;
		case 0x7: // 7XNN: Adds NN to register VX, ignores overflows
			registers[x] += nn;
			break;
		case 0x8:
			break;
		case 0x9:
			break;
		case 0xA: // ANNN: Sets index register to NNN
			index_register = nnn;
			break;
		case 0xB:
			break;
		case 0xC:
			break;
		case 0xD: // DXYN: Draw n pixels at x,y
			draw(registers[x] % WIDTH, registers[y] % HEIGHT, n);
			break;
		case 0xE:
			break;
		case 0xF:
			break;
		default:
			printf("Error: Unknown instruction identifier");
			exit(EXIT_FAILURE);
	}
}
