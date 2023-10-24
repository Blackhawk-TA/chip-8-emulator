//
// Created by daniel on 24.10.23.
//

#ifndef CHIP_8_EMULATOR_RENDERER_H
#define CHIP_8_EMULATOR_RENDERER_H

#include <SDL2/SDL.h>

/**
 * Is run on every render iteration of the SDL renderer.
 * @param renderer The SDL renderer used to draw on the screen
 */
void render_loop(SDL_Renderer *renderer);

#endif //CHIP_8_EMULATOR_RENDERER_H
