#include "game_state.h"

int frame_start = 0;

game_state_t g_init(unsigned scrw, unsigned scrh, int target_fps) {
	game_state_t game_state;
	game_state.is_debug_mode = false;
	game_state.is_running = true;
	game_state.scr_h = scrh;
	game_state.scr_w = scrw;
	game_state.target_fps = target_fps;
	game_state.target_frametime = 1.0 / (double)game_state.target_fps;
	game_state.is_fps_capped = false;
	game_state.delta_time = game_state.target_frametime;
	game_state.is_debug_mode = false;
	
	return game_state;
}

void g_startFrame() {
	frame_start = SDL_GetTicks();
}

void g_endFrame(game_state_t* game_state) {
	game_state->delta_time = (SDL_GetTicks() - frame_start) /  1000.0;
	
	if (game_state->delta_time < game_state->target_frametime) {
		SDL_Delay((game_state->target_frametime - game_state->delta_time) * 1000.0);
		game_state->delta_time = game_state->target_frametime;
	}
}