//
// Created by daniel on 23.10.23.
//

#include "sdl_wrapper.h"
#include "renderer.h"
#include "../components/cpu.h"
#include "../utils/utils.h"
#include "../components/display.h"
#include "../components/keypad.h"

static const uint8_t SCALE = 10;
static const uint64_t ONE_NANOSECOND = 1000000000;
static const uint8_t MAX_FPS = 60;

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

	SDL_Event event;
	int quit = 0;

	uint64_t last_frame_draw_time = get_time_ns();
	uint64_t current_time;

	while (!quit) {
		// Handle interruption
		SDL_PollEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYUP:
				update_key_status(event.key.keysym.scancode, 0);
				break;
			case SDL_KEYDOWN:
				update_key_status(event.key.keysym.scancode, 1);
				break;
		}

		current_time = get_time_ns();
		cpu_cycle(); // Handle one cpu instruction

		// Limit FPS for render loop
		if (current_time - last_frame_draw_time >= ONE_NANOSECOND / MAX_FPS) {
			render_loop(renderer);
			SDL_RenderPresent(renderer);

			// print_fps(current_time, last_frame_draw_time);

			// Update last_time to the time the last frame
			last_frame_draw_time = get_time_ns();
		}

		SDL_Delay(1); // Run loop only 1000x per second, which limits the instructions per second.
	}

	// Event loop and cleanup code will also go here.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void print_fps(uint64_t current_time, uint64_t last_frame_draw_time) {
	float delta_time = (float)(current_time - last_frame_draw_time);
	if (delta_time == 0.0) { // Prevent division by 0
		delta_time = 1.0f;
	}
	printf("FPS: %.2f\n", (float)ONE_NANOSECOND / delta_time);
}

void sdl_draw_px(SDL_Renderer *renderer, uint8_t x, uint8_t y, uint8_t state) {
	if (state == 0) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set to color to black
	} else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set to color to white => monochrome display
	}
	SDL_Rect rect = {x * SCALE, y * SCALE, 1 * SCALE, 1 * SCALE};
	SDL_RenderFillRect(renderer, &rect);
}
