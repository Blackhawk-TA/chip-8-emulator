//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_CPU_H
#define CHIP_8_EMULATOR_CPU_H

#include <stdint.h>

extern uint32_t CLOCK_SPEED_HZ;

void cpu_cycle();

/**
 * Fetch the instruction from memory at the current program counter (PC)
 * @return The instruction at which the PC points at
 */
uint8_t fetch();

void decode();
void execute();

#endif //CHIP_8_EMULATOR_CPU_H
