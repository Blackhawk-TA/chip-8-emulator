//
// Created by daniel on 24.10.23.
//

#include "renderer.h"
#include "sdl_wrapper.h"
#include "../components/timer.h"

void render_loop(SDL_Renderer *renderer) {
	// Update timers
	delay_timer_run();
	sound_timer_run();

	// Render pixels for testing
	draw_px(renderer, 1, 1);
	draw_px(renderer, 2, 1);
}
