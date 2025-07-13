#include "renderer.h"

SDL_Window* window;

void r_init(SDL_Window* main_window, game_state_t *game_state) {
	
}
void r_destroy() {
	
}
void r_render(game_state_t* game_state, player_t* player) {
	
}
void r_drawWalls(game_state_t* game_state, player_t* player) {
	
}
sector_t r_createSector(int height, int elevation, unsigned color, unsigned ceil_color, unsigned floor_color) {
	
}
void r_sectorAddWall(sector_t *sector, wall_t vertices) {
	
}
void r_queueSector(sector_t* sector) {
	
}
wall_t r_createWall(int ax, int ay, int bx, int by) {
	
}
wall_t r_createPortal(int ax, int ay, int bx, int by, int th, int bh) {
	
}
