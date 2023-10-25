//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_TIMER_H
#define CHIP_8_EMULATOR_TIMER_H

#include <stdint.h>

extern uint8_t delay_timer;
extern uint8_t sound_timer;

void delay_timer_run();
void sound_timer_run();

#endif //CHIP_8_EMULATOR_TIMER_H
