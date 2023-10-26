//
// Created by daniel on 23.10.23.
//

#include "display.h"
#include "memory.h"

#define BYTE_LENGTH 8

const uint8_t WIDTH = 64;
const uint8_t HEIGHT = 32;
uint8_t display[64][32] = {};

void draw(uint8_t x, uint8_t y, uint8_t n) {
	uint8_t px_byte, px_bit;
	uint8_t *display_px;
	registers[0XF] = 0; // 0xF is the flag register

	for (uint8_t byte_index = 0; byte_index < n && y < HEIGHT; byte_index++) {
		px_byte = memory_read(index_register + byte_index);

		for (uint8_t bit_index = 0; bit_index < BYTE_LENGTH && x < WIDTH; bit_index++) {
			px_bit = (px_byte >> (7 - bit_index)) & 0b1; // Get the bits from left to right

			if (px_bit == 1) {
				display_px = &display[x + bit_index][y + byte_index];
				if (*display_px == 1) {
					registers[0xF] = 1;
				}
				*display_px ^= 1;
			}
		}
	}
}

void clear_display() {
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			display[x][y] = 0;
		}
	}
}
