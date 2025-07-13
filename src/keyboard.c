#include "keyboard.h"

double SPEED = 150.0;
double ELEV_SPEED = 500 * 100;
double ROT_SPEED = 4;

void k_handleEvents(game_state_t* game_state, player_t* player) {
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_KEYDOWN:
			keys[event.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.scancode] = false;
			break;
		case SDL_QUIT:
			game_state->is_running = false;
			break;
		default:
			break;
	}
}
void k_processKeystates(player_t* player, double deltaTime) {
	if (keys[move_forward]) {
		player->position.x += SPEED * cos(player->dir_angle) * deltaTime;
		player->position.y += SPEED * sin(player->dir_angle) * deltaTime;
	}
	if (keys[move_backward]) {
		player->position.x -= SPEED * cos(player->dir_angle) * deltaTime;
		player->position.y -= SPEED * sin(player->dir_angle) * deltaTime;		
	}
	if (keys[strafe_left]) {
		player->position.x += SPEED * cos(player->dir_angle) * deltaTime;
		player->position.y += SPEED * sin(player->dir_angle) * deltaTime;
	}
	if (keys[strafe_right]) {
		player->position.x += SPEED * cos(player->dir_angle) * deltaTime;
		player->position.y += SPEED * sin(player->dir_angle) * deltaTime;
	}
	if (keys[move_left]) {
		player->dir_angle += ROT_SPEED * deltaTime;
	}
	if (keys[move_right]) {
		player->dir_angle -= ROT_SPEED * deltaTime;
	}
}