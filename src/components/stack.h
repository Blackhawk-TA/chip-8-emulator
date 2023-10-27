//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_STACK_H
#define CHIP_8_EMULATOR_STACK_H

#include <stdint.h>

void init_stack();
void stack_push(uint16_t value);
uint16_t stack_pop();

#endif //CHIP_8_EMULATOR_STACK_H
