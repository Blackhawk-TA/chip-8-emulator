//
// Created by daniel on 23.10.23.
//

#include "display.h"
#include "memory.h"

const uint8_t WIDTH = 64;
const uint8_t HEIGHT = 32;
uint8_t display[64][32] = {};

void draw(uint8_t x, uint8_t y, uint8_t n) {
	uint8_t px_byte, px_bit;
	uint8_t x_modified = x;
	uint8_t y_modified = y;
	registers[0XF] = 0; // Set flag register to 0

	for (uint8_t i = 0; i < n; i++) {
		px_byte = memory_read(index_register + i);
		x_modified = x;

		for(uint8_t bit_index = 0; bit_index < 8; bit_index++) {
			px_bit = (px_byte >> (7 - bit_index)) & 0b1; // Get the bits from left to right

			if (px_bit == 1 && display[x_modified][y_modified] == 1) { //TODO optimize
				display[x_modified][y_modified] = 0;
				registers[0xF] = 1;
			} else if (px_bit == 1 && display[x_modified][y_modified] == 0) {
				display[x_modified][y_modified] = 1;
			}

			if (x_modified == WIDTH - 1) {
				break;
			}
			x_modified++;
		}
		if (y_modified == HEIGHT - 1) {
			break;
		}
		y_modified++;
	}
}

void clear_display() {
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			display[x][y] = 0;
		}
	}
}
