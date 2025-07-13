#include <stdio.h>

#include "player.h"
#include "game_state.h"
#include "window.h"
#include "renderer.h"
#include "keyboard.h"



void gameRun(game_state_t* game_state, player_t* player) {
	while (game_state->is_running) {
		g_startFrame();
		
		k_handleEvents(game_state, player);
		r_render(game_state, player);
		
		g_endFrame(game_state);
	}
}

int main(int argc, char **argv)
{
	game_state_t game_state = g_init(WIDTH, HEIGHT, FPS);
	player_t player = p_init(40, 40, WIDTH * 10, M_PI/2);
	k_initKeymap();
	w_init(WIDTH, HEIGHT);
	r_init(w_get(), &game_state);
	
	sector_t s0 = r_createSector(10, 0, 0xffffff, 0xcccccc, 0xff00ff);
	
	int s1v[4*4] = {
		70, 220, 100, 220,
		100, 220, 100, 240,
		100, 240, 70, 240,
		70, 240, 70, 220
	};
	
	gameRun(&game_state, &player);
	
	return 0;
}

