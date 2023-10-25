//
// Created by daniel on 24.10.23.
//

#include "cpu.h"
#include "memory.h"

u_int32_t CLOCK_SPEED_HZ = 1000000; // 1 MHz

void cpu_cycle() {
}

u_int8_t fetch() {
	return memory_read(program_counter);
}