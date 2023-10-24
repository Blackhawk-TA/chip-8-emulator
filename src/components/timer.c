//
// Created by daniel on 24.10.23.
//

#include "timer.h"

static u_int8_t delay_timer = 60;
static u_int8_t sound_timer = 60;

void set_delay_timer(u_int8_t value) {
	delay_timer = value;
}

u_int8_t get_delay_timer() {
	return delay_timer;
}

void delay_timer_run() {
	if (delay_timer > 0) {
		delay_timer--;
	} else {
		delay_timer = 60;
	}
}

void sound_timer_run() {
	if (sound_timer > 0) {
		sound_timer--;
	} else {
		sound_timer = 60;
	}
}
