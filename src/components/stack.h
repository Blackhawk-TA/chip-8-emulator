//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_STACK_H
#define CHIP_8_EMULATOR_STACK_H

#include <stdlib.h>

void init_stack();
void stack_push(u_int8_t value);
u_int16_t stack_pop();

#endif //CHIP_8_EMULATOR_STACK_H
