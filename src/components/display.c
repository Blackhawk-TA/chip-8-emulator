//
// Created by daniel on 23.10.23.
//

#include "display.h"

const uint8_t WIDTH = 64;
const uint8_t HEIGHT = 32;
uint8_t display[64][32] = {};

void draw(uint8_t x, uint8_t y, uint8_t range) {
	for (int i = 0; i < range; i++) {
		display[x + i][y] = 1; //TODO: implement properly
	}
}

void clear_display() {
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			display[x][y] = 0;
		}
	}
}
