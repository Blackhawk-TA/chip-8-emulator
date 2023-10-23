//
// Created by daniel on 23.10.23.
//

#ifndef CHIP_8_EMULATOR_SDL_WRAPPER_H
#define CHIP_8_EMULATOR_SDL_WRAPPER_H

#include <SDL2/SDL.h>

void init_sdl();
uint32_t time_left();
void draw_px(SDL_Renderer *renderer, uint8_t x, uint8_t y);

#endif //CHIP_8_EMULATOR_SDL_WRAPPER_H
