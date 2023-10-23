//
// Created by daniel on 23.10.23.
//

#ifndef CHIP_8_EMULATOR_MEMORY_H
#define CHIP_8_EMULATOR_MEMORY_H

#include "utils.h"
#include <stdlib.h>

u_int8_t memory_read(u_int16_t address);
void memory_write(u_int16_t address, u_int8_t value);

#endif //CHIP_8_EMULATOR_MEMORY_H
