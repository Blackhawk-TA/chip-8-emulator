//
// Created by daniel on 23.10.23.
//

#include "sdl_wrapper.h"
#include "renderer.h"
#include "../components/cpu.h"
#include "../utils/utils.h"
#include "../components/display.h"

static const uint8_t SCALE = 10;
static const uint64_t ONE_NANOSECOND = 1000000000;
static uint8_t MAX_FPS = 60;

void init_sdl() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL initialization failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * SCALE, HEIGHT * SCALE, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("Window creation failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set to color to white => monochrome display

	SDL_Event event;
	int quit = 0;

	uint64_t last_fps_time = get_time_ns();
	uint64_t last_cpu_time = get_time_ns();
	uint64_t counter = 0;
	uint64_t current_time;
	float delta_time, fps;

	while (!quit) {
		// TODO: This messes with the loop speed
		// Handle interruption
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
		}

		current_time = get_time_ns();

		// Handle CPU cycles
		if (current_time - last_cpu_time >= ONE_NANOSECOND / CLOCK_SPEED_HZ) {
			counter++;
			cpu_cycle();
		}
		last_cpu_time = get_time_ns();

		// Limit FPS for render loop
		if (current_time - last_fps_time < ONE_NANOSECOND / MAX_FPS) {
			continue;
		}
		printf("%lu\n", counter);
		counter = 0;

		render_loop(renderer);
		SDL_RenderPresent(renderer);

		// Calculate FPS
		delta_time = (float)(current_time - last_fps_time);
		if (delta_time == 0.0) { // Prevent division by 0
			delta_time = 1.0f;
		}
		fps = (float)ONE_NANOSECOND / delta_time;
		printf("FPS: %.2f\n", fps);

		// Update last_ticks for next iteration
		last_fps_time = get_time_ns();
	}

	// Event loop and cleanup code will also go here.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void draw_px(SDL_Renderer *renderer, uint8_t x, uint8_t y) {
	SDL_Rect rect = {x * SCALE, y * SCALE, 1 * SCALE, 1 * SCALE};
	SDL_RenderFillRect(renderer, &rect);
}
