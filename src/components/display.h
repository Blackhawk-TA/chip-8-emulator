//
// Created by daniel on 23.10.23.
//

#ifndef CHIP_8_EMULATOR_DISPLAY_H
#define CHIP_8_EMULATOR_DISPLAY_H

#include <stdint.h>

extern const uint8_t WIDTH;
extern const uint8_t HEIGHT;
extern uint8_t display[64][32]; //TODO: can be done without 2D array. Faster but more implementation effort.

void draw(uint8_t initial_x, uint8_t initial_y, uint8_t n);
void clear_display();

#endif //CHIP_8_EMULATOR_DISPLAY_H
