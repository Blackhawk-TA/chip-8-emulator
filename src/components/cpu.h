//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_CPU_H
#define CHIP_8_EMULATOR_CPU_H

#include <stdint.h>

extern uint32_t CLOCK_SPEED_HZ;

void cpu_cycle();

/**
 * Fetch the instruction from memory at the current program counter (PC) and increments it by 2.
 * The instruction consists of a 16bit value, therefore reading two 8bit entries in memory is necessary.
 * @return The instruction at which the PC points at
 */
uint16_t fetch();

void decode_and_execute(uint16_t instruction);

#endif //CHIP_8_EMULATOR_CPU_H
