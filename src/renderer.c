#include "renderer.h"

SDL_Window* window;
SDL_Renderer* sdl_renderer;
SDL_Texture* screen_texture;
unsigned int scrw, scrh;
unsigned int* screen_buffer;
int screen_buffer_size;

sector_queue_t sector_queue;

void r_clearScreenBuffer() {
	memset(screen_buffer, 0, sizeof(unsigned) * scrw * scrh);
}

void r_initScreen(int w, int h) {
	screen_buffer_size = sizeof(unsigned int) * w * h;
	screen_buffer = (unsigned int*)malloc(screen_buffer_size);
	if (!screen_buffer) {
		screen_buffer_size = -1;
		printf("Error initializing screen buffer\n");
		r_destroy();
	}
	
	r_clearScreenBuffer();
	
	screen_texture = SDL_CreateTexture(
		sdl_renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		w, h
	);
	
	if (!screen_texture) {
		printf("Error creating screen texture\n");
		r_destroy();
	}
}

void r_init(SDL_Window* main_window, game_state_t *game_state) {
	window = main_window;
	scrw = game_state->scr_w;
	scrh = game_state->scr_h;
	
	sdl_renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	r_initScreen(scrw, scrh);
	SDL_RenderSetLogicalSize(sdl_renderer, scrw, scrh);
}
void r_destroy() {
	if (screen_texture)
		SDL_DestroyTexture(screen_texture);
	if (screen_buffer)
		free(screen_buffer);
	SDL_DestroyRenderer(sdl_renderer);
}
void r_updateScreen() {
	SDL_UpdateTexture(screen_texture, NULL, screen_buffer, scrw * sizeof(unsigned int));
	SDL_RenderCopy(sdl_renderer, screen_texture, NULL, NULL);
	SDL_RenderPresent(sdl_renderer);
}

void r_drawPoint(int x, int y, unsigned int color) {
	bool is_out_of_bounds = (x < 0 || x >= scrw || y < 0 || y >= scrh);
	bool is_outside_mem_buf = (scrw * y + x) >= (scrw * scrh);
	
	if (is_out_of_bounds || is_outside_mem_buf) return;
	
	screen_buffer[scrw * y + x] = color;
}

void r_drawLine(int x0, int y0, int x1, int y1, unsigned int color)
{
    int dx;
    if (x1 > x0)
        dx = x1 - x0;
    else
        dx = x0 - x1;

    int dy;
    if (y1 > y0)
        dy = y1 - y0;
    else
        dy = y0 - y1;

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        r_drawPoint(x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void r_renderSectors(player_t* player, game_state_t* game_state) {
	double scr_half_w = scrw / 2;
	double scr_half_h = scrh / 2;
	unsigned wall_color = 0xffff00ff;
	
	r_clearScreenBuffer();
	
	for (int i = 0; i < sector_queue.sector_ct; i++) {
		sector_t* s = &sector_queue.sectors[i];
		
		for (int k = 0; k < s->wall_ct; k++) {
			wall_t *w = &s->walls[k];
			
			//transform based on player position
			double dx1 = w->a.x - player->position.x;
			double dy1 = w->a.y - player->position.y;
			double dx2 = w->b.x - player->position.x;
			double dy2 = w->b.y - player->position.y;
			
			//rotate based on player rotation
			double sn = sin(player->dir_angle);
			double cs = cos(player->dir_angle);
			double wx1 = dx1 * sn - dy1 * cs;
			double wz1 = dx1 * cs + dy1 * sn;
			double wx2 = dx2 * sn - dy2 * cs;
			double wz2 = dx2 * cs + dy2 * sn;
			
			//wall height calculation
			double wh1 = (s->height / wz1) * FOV;
			double wh2 = (s->height / wz2) * FOV;
			
			//screen space conversion
			double sx1 = (wx1 / wz1) * FOV;
			double sy1 = ((game_state->scr_h + player->z) / wz1);
			double sx2 = (wx2 / wz2) * FOV;
			double sy2 = ((game_state->scr_h + player->z) / wz2);
			
			//calculate wall elevation
			double s_level1 = (s->elevation / wz1) * FOV;
			double s_level2 = (s->elevation / wz2) * FOV;
			sy1 -= s_level1;
			sy2 -= s_level2;
			
			//construct portal top and bottom
			double pth1, pth2, pbh1, pbh2;
			if (w->is_portal) {
				pth1 = (w->portal_top_height / wz1) * FOV;
				pth2 = (w->portal_top_height / wz2) * FOV;
				pbh1 = (w->portal_bot_height / wz1) * FOV;
				pbh2 = (w->portal_bot_height / wz2) * FOV;
			}
			
			//set origin to center of screen
			sx1 += scr_half_w;
			sy1 += scr_half_h;
			sx2 += scr_half_w;
			sy2 += scr_half_h;
			
			//top
			r_drawLine(sx1, sy1 - wh1, sx2, sy2 - wh2, wall_color);
			//bottom
			r_drawLine(sx1, sy1, sx2, sy2, wall_color);
			//left
			r_drawLine(sx1, sy1 - wh1, sx1, sy1, wall_color);
			//right
			r_drawLine(sx2, sy2 - wh2, sx2, sy2, wall_color);
		}
	}
}

void r_render(game_state_t* game_state, player_t* player) {
	
	r_renderSectors(player, game_state);
	r_updateScreen();
	
}
void r_drawWalls(game_state_t* game_state, player_t* player) {
	
}
sector_t r_createSector(int height, int elevation, unsigned color, unsigned ceil_color, unsigned floor_color) {
	static int sector_id = 0;
	sector_t sector = {0};
	sector.wall_ct = 0;
	sector.height = height;
	sector.elevation = elevation;
	sector.color = color;
	sector.ceil_color = ceil_color;
	sector.floor_color = floor_color;
	sector.id = ++sector_id;
	
	return sector;
}
void r_sectorAddWall(sector_t *sector, wall_t vertices) {
	sector->walls[sector->wall_ct] = vertices;
	sector->wall_ct++;
}
void r_queueSector(sector_t* sector) {
	sector_queue.sectors[sector_queue.sector_ct] = *sector;
	sector_queue.sector_ct++;
}
wall_t r_createWall(int ax, int ay, int bx, int by) {
		wall_t w;
		w.a.x = ax;
		w.a.y = ay;
		w.b.x = bx;
		w.b.y = by;
		w.is_portal = false;
		
		return w;
}
wall_t r_createPortal(int ax, int ay, int bx, int by, int th, int bh) {
	
}
