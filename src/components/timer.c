//
// Created by daniel on 24.10.23.
//

#include "timer.h"

uint8_t delay_timer = 60;
uint8_t sound_timer = 60;

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
