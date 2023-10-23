//
// Created by daniel on 23.10.23.
//

#ifndef CHIP_8_EMULATOR_MEMORY_H
#define CHIP_8_EMULATOR_MEMORY_H

#include "utils.h"

uint8 read(uint16 address);
void write(uint16 address, uint8 value);

void load_font();
void load_rom();

#endif //CHIP_8_EMULATOR_MEMORY_H
