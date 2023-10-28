//
// Created by daniel on 24.10.23.
//

#include "keypad.h"

static uint8_t key_status[16] = {};

uint8_t is_key_pressed(uint8_t key) {
	return key_status[key];
}

int8_t get_pressed_key() {
	int8_t i = 0;
	uint8_t is_pressed = 0;
	int8_t key = -1;

	while (is_pressed == 0 && i < sizeof(key_status) / sizeof(key_status[0])) {
		is_pressed = key_status[i];
		key = i;
		i++;
	}

	return key;
}

void update_key_status(uint16_t scancode, uint8_t status) {
	switch (scancode) { // Comments refer to QWERTZ keyboard layout transformed to COSMAC VIP hex layout
		case 30: // Key: 1 => 1
			key_status[0x1] = status;
			break;
		case 31: // Key: 2 => 2
			key_status[0x2] = status;
			break;
		case 32: // Key: 3 => 3
			key_status[0x3] = status;
			break;
		case 33: // Key: 4 => C
			key_status[0xC] = status;
			break;
		case 20: // Key: Q => 4
			key_status[0x4] = status;
			break;
		case 26: // Key: W => 5
			key_status[0x5] = status;
			break;
		case 8: // Key: E => 6
			key_status[0x6] = status;
			break;
		case 21: // Key: R => D
			key_status[0xD] = status;
			break;
		case 4: // Key: A => 7
			key_status[0x7] = status;
			break;
		case 22: // Key: S => 8
			key_status[0x8] = status;
			break;
		case 7: // Key: D => 9
			key_status[0x9] = status;
			break;
		case 9: // Key: F => E
			key_status[0xE] = status;
			break;
		case 29: // Key: Y => A
			key_status[0xA] = status;
			break;
		case 27: // Key: X => 0
			key_status[0x0] = status;
			break;
		case 6: // Key: C => B
			key_status[0xB] = status;
			break;
		case 25: // Key: V => F
			key_status[0xF] = status;
			break;
		default:
			break;
	}
}
