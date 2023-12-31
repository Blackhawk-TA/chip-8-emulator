//
// Created by daniel on 23.10.23.
//

#ifndef CHIP_8_EMULATOR_SDL_WRAPPER_H
#define CHIP_8_EMULATOR_SDL_WRAPPER_H

#include <SDL2/SDL.h>

/**
 * Sets up an SDL window with rendering loop
 */
void init_sdl();

/**
 * Draws the current fps count into the console
 * @param current_time The current time in the sdl loop in ns
 * @param last_frame_draw_time The last time a frame was rendered in ms
 */
void print_fps(uint64_t current_time, uint64_t last_frame_draw_time);

/**
 * Draws a pixel on the screen on the given position.
 * Scales it up 10x for better visibility, because CHIP-8 has only a 64x32 screen.
 * @param renderer The SDL renderer
 * @param x The x position of the pixel
 * @param y The y position of the pixel
 * @param state The state of the pixel to draw. If set to 0, the pixel is black, else it is white
 */
void sdl_draw_px(SDL_Renderer *renderer, uint8_t x, uint8_t y, uint8_t state);

#endif //CHIP_8_EMULATOR_SDL_WRAPPER_H
