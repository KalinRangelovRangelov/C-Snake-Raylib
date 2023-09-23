#ifndef GAME_DEF_H
#define GAME_DEF_H

#include "renderer_def.h"
#include "particles.h"

void game_init(int grid_size, float snake_speed); 
void game_end();
void game_draw(); // renderer?
void game_update(double *last_time_frame, double current_time_frame);
void game_handle_input();


typedef struct {
	int grid_size;
	float snake_speed;
	int score;
	int best_score;

	void (*init)(int grid_size, float snake_speed);
	void (*end)();
	void (*update)(double *last_time_frame, double current_time_frame);
	void (*handle_input)();
} Game;

Game game = {
	.init = game_init, 
	.end  = game_end,
	.update = game_update, 
	.handle_input = game_handle_input
};

void game_init(int grid_size, float snake_speed) {
	game.grid_size = grid_size;
	game.snake_speed = snake_speed;
	int center = grid_size / 2;
	snake_init(center, center, UP);
	snake_grow();
	snake_grow();
	apple_generate(grid_size, grid_size);
}

void game_end() {
	if(game.best_score < game.score) {
		game.best_score = game.score;
	}
	game.score = 0;
	snake_release();
	game.init(game.grid_size, game.snake_speed);
}

void game_update(double *last_time_frame, double current_time_frame) {
	if(current_time_frame > *last_time_frame + game.snake_speed) {
		snake_move();
		if(detect_apple(game.grid_size)) {
			game.score++;
			size_t x = apple.x * SCALE + GRID_OFFSET;
			size_t y = apple.y * SCALE + GRID_OFFSET;
			particles_spawn((Vector2){x, y}, MAX_PARTICLES);
			snake_grow();
			apple_generate(game.grid_size, game.grid_size);
		}
		particles_party();
		if(detect_collision(game.grid_size)) {
			game.end();
		}
		*last_time_frame = current_time_frame;
	}
}


#endif // GAME_DEF_H