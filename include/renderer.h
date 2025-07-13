#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "typedefs.h"
#include "player.h"
#include "game_state.h"
#include "utils.h"
#include "settings.h"

typedef struct {
	int t[1024];
	int b[1024];
} plane_lut_t;

typedef struct {
	vec2_t a, b;
	double portal_top_height;
	double portal_bot_height;
	bool is_portal;
} wall_t;

typedef struct {
	int id;
	wall_t walls[10];
	int wall_ct;
	int height, elevation;
	double dist;
	unsigned color, floor_color, ceil_color;
	
	plane_lut_t portals_floor_xylut,
				portals_ceil_xylut,
				floor_xylut,
				ceil_xylut;
} sector_t;

typedef struct {
	sector_t sectors[1024];
	int sector_ct;
} sector_queue_t;

void r_init(SDL_Window* main_window, game_state_t *game_state);
void r_destroy();
void r_render(game_state_t* game_state, player_t* player);
void r_drawWalls(game_state_t* game_state, player_t* player);
sector_t r_createSector(int height, int elevation, unsigned color, unsigned ceil_color, unsigned floor_color);
void r_sectorAddWall(sector_t *sector, wall_t vertices);
void r_queueSector(sector_t* sector);
wall_t r_createWall(int ax, int ay, int bx, int by);
wall_t r_createPortal(int ax, int ay, int bx, int by, int th, int bh);
#endif