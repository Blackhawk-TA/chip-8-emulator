//
// Created by daniel on 23.10.23.
//

#ifndef CHIP_8_EMULATOR_SETUP_H
#define CHIP_8_EMULATOR_SETUP_H

/**
 * Loads the ROM from a file path into the memory starting at address 0x200
 * @param path The path to the ROM on the filesystem
 */
void load_rom_file(char* path);

/**
 * Loads the font into the memory at the address range 0x050 - 0x09F
 */
void load_font();

#endif //CHIP_8_EMULATOR_SETUP_H
