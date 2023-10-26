//
// Created by daniel on 23.10.23.
//

#include "display.h"

const uint8_t WIDTH = 64;
const uint8_t HEIGHT = 32;
uint8_t display[64][32] = {};

void draw(uint8_t x, uint8_t y, uint8_t range) {
	for (int i = 0; i < range; i++) {
		display[x][y] = 1; //TODO: implement properly
	}
}
