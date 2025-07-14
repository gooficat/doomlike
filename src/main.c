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
	player_t player = p_init(40, 40, WIDTH * 5, M_PI/2);
	
	w_init(WIDTH, HEIGHT);
	r_init(w_get(), &game_state);
	
	sector_t s0 = r_createSector(10, 0, 0xd6382d, 0xf54236, 0x9c2921);
	sector_t s1 = r_createSector(80, 0, 0x29ba48, 0x43f068, 0x209138);
	
	int s1v[4*4] = {
		70, 220, 100, 220,
		100, 220, 100, 240,
		100, 240, 70, 240,
		70, 240, 70, 220
	};

	int s2v[4*4] = {
		30, 120, 40, 120,
		40, 120, 40, 190,
		40, 190, 30, 190,
		30, 190, 30, 120
	};
	
	for (int i = 0; i < 16; i += 4) {
		wall_t w = r_createWall(s1v[i], s1v[i+1], s1v[i+2], s1v[i+3]);
		r_sectorAddWall(&s0, w);
		w = r_createPortal(s2v[i], s2v[i+1], s2v[i+2], s2v[i+3], 20, 10);
		r_sectorAddWall(&s1, w);
	}
	
	r_queueSector(&s0);	
	r_queueSector(&s1);
	
	gameRun(&game_state, &player);
	
	return 0;
}

