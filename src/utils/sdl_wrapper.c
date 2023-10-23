//
// Created by daniel on 23.10.23.
//

#include "sdl_wrapper.h"

static const uint8_t SCALE = 10;
static const uint32_t TICK_INTERVAL = 16;
static uint32_t next_time;

void init_sdl() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL initialization failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window* window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("Window creation failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set to color to white => monochrome display

	SDL_Event event;
	int quit = 0;
	next_time = SDL_GetTicks64() + TICK_INTERVAL;

	uint32_t start_time, current_time;
	double delta_time, fps;

	while (!quit) {
		start_time = SDL_GetTicks64();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
		}

		// Additional rendering or game logic can go here.
		draw_px(renderer, 1, 1);
		draw_px(renderer, 2, 1);

		SDL_RenderPresent(renderer);

		// Limit framerate
		SDL_Delay(time_left());
		next_time += TICK_INTERVAL;

		// Calculate FPS
		current_time = SDL_GetTicks64();
		delta_time = (double)(current_time - start_time) / 1000.0f;

		if (delta_time == 0.0) {
			delta_time = 1.0;
		}
		fps = 1 / delta_time;
		printf("FPS: %.2f\n", fps);
	}

	// Event loop and cleanup code will also go here.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

uint32_t time_left() {
	uint32_t now = SDL_GetTicks64();

	if (next_time <= now) {
		return 0;
	}
	return next_time - now;
}

void draw_px(SDL_Renderer *renderer, uint8_t x, uint8_t y) {
	SDL_Rect rect = {x * SCALE, y * SCALE, 1 * SCALE, 1 * SCALE};
	SDL_RenderFillRect(renderer, &rect);
}
