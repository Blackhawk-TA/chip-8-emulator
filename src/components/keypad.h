//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_KEYPAD_H
#define CHIP_8_EMULATOR_KEYPAD_H

#include <stdint.h>

/**
 * Checks in the key_status array if a key is pressed.
 * @param key The name of the key, which is a hex value from 0 - F
 * @return Returns 1 if key is pressed, otherwise 0
 */
uint8_t is_pressed(uint8_t key);

/**
 * Updates the status of the given key.
 * @param scancode The scancode of the key
 * @param status The status of the key. 1 if the key is pressed, 0 on key release
 */
void update_key_status(uint16_t scancode, uint8_t status);

#endif //CHIP_8_EMULATOR_KEYPAD_H
