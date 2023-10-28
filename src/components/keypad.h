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
uint8_t is_key_pressed(uint8_t key);

/**
 * Checks if the given key was released.
 * @param key The hex number of the key
 * @return Returns 1 if it was released, else 0
 */
uint8_t is_key_released(int8_t key);

/**
 * Checks if a key is pressed and returns the first key that was pressed in the hex key array.
 * @return Returns the key hex value 0-F if a key is pressed, otherwise return -1.
 */
int8_t get_pressed_key();

/**
 * Updates the status of the given key.
 * @param scancode The scancode of the key
 * @param status The status of the key. 1 if the key is pressed, 0 on key release
 */
void update_key_status(uint16_t scancode, uint8_t status);

#endif //CHIP_8_EMULATOR_KEYPAD_H
