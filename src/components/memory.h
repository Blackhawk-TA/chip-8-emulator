//
// Created by daniel on 23.10.23.
//

#ifndef CHIP_8_EMULATOR_MEMORY_H
#define CHIP_8_EMULATOR_MEMORY_H

#include "../utils/utils.h"
#include <stdint.h>

#define FONT_START_ADDR 0x50
#define FONT_BYTES_PER_CHAR 5
#define ROM_START_ADDR 0x200

extern uint16_t program_counter; // Points at the current instruction in memory
extern uint16_t index_register; // Points at locations in memory
extern uint8_t registers[16]; //The CPU registers V0 - VF TODO: error handling for wrong access

void init_memory();
uint8_t memory_read(uint16_t address);
void memory_write(uint16_t address, uint8_t value);

#endif //CHIP_8_EMULATOR_MEMORY_H
