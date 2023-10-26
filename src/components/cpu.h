//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_CPU_H
#define CHIP_8_EMULATOR_CPU_H

#include <stdint.h>

extern uint32_t CLOCK_SPEED_HZ;

/**
 * Fetches, decodes and executes the instruction at which the program counter points.
 */
void cpu_cycle();

/**
 * Fetch the instruction from memory at the current program counter (PC) and increments it by 2.
 * The instruction consists of a 16bit value, therefore reading two 8bit entries in memory is necessary.
 * @return The instruction at which the PC points at
 */
uint16_t fetch();

/**
 * Decodes the instruction into its individual parts and executes it.
 * @param instruction The 16bit instruction value
 */
void decode_and_execute(uint16_t instruction);

/**
 * Handles an unknown instruction by printing an error message and existing.
 * @param instruction The instruction hex value which is unknown
 */
void unknown_instruction(uint16_t instruction);

#endif //CHIP_8_EMULATOR_CPU_H
