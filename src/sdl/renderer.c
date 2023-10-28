//
// Created by daniel on 24.10.23.
//

#include "renderer.h"
#include "sdl_wrapper.h"
#include "../components/timer.h"
#include "../components/display.h"

void render_loop(SDL_Renderer *renderer) {
	// Update timers
	delay_timer_run();
	sound_timer_run();

	// Render pixels of the entire display
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			sdl_draw_px(renderer, x, y, display[x][y]);
		}
	}
}
