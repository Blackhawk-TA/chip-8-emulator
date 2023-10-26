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
 * Draws a pixel on the screen on the given position.
 * Scales it up 10x for better visibility, because CHIP-8 has only a 64x32 screen.
 * @param renderer The SDL renderer
 * @param x The x position of the pixel
 * @param y The y position of the pixel
 */
void sdl_draw_px(SDL_Renderer *renderer, uint8_t x, uint8_t y);

#endif //CHIP_8_EMULATOR_SDL_WRAPPER_H
