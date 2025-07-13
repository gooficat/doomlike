#ifndef GAME_STATE_H
#define GAME_STATE_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "typedefs.h"

typedef struct {
	unsigned scr_w, scr_h;
	double target_fps, target_frametime, delta_time;
	bool is_running, is_paused;
	bool is_fps_capped, state_show_map, is_debug_mode;
} game_state_t;

game_state_t g_init(unsigned scrw, unsigned scrh, int target_fps);
void g_startFrame();
void g_endFrame(game_state_t* game_state);
#endif