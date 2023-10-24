//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_TIMER_H
#define CHIP_8_EMULATOR_TIMER_H

#include <stdlib.h>

void set_delay_timer(u_int8_t value);
u_int8_t get_delay_timer();
void delay_timer_run();
void sound_timer_run();

#endif //CHIP_8_EMULATOR_TIMER_H
