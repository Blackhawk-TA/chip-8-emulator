//
// Created by daniel on 23.10.23.
//

#ifndef CHIP_8_EMULATOR_UTILS_H
#define CHIP_8_EMULATOR_UTILS_H

#include <stdint.h>

/**
 * Gets the value of the input parameter "--rom" which is the path to the ROM on the filesystem
 * @param argv The input parameters handed over from the main function
 * @return A string with the ROM path on the filesystem
 */
char* get_path_from_parameter(char **argv);

uint64_t get_time_ns();

#endif //CHIP_8_EMULATOR_UTILS_H
