#ifndef GAME_DEF_H
#define GAME_DEF_H


void game_init(int grid_size, float snake_speed); 
void game_end();
void game_loop();
void game_draw(); // renderer?
void game_update(double *last_time_frame, double current_time_frame);
void game_handle_input();


typedef struct {
	int grid_size;
	float snake_speed;

	void (*init)(int grid_size, float snake_speed);
	void (*end)();
	void (*loop)();
	void (*draw)();
	void (*update)();
	void (*handle_input)(double *last_time_frame, double current_time_frame);
		
} Game;

Game game = {
	.init = game_init, 
	.end  = game_end,
	.loop = game_loop,
	.draw = game_draw,
	.update = game_update, 
	.handle_input = game_handle_input
	
};

#ifndef GAME_DEF_IMPLEMENTATION
#define GAME_DEF_IMPLEMENTATION

void game_init(int grid_size, float snake_speed) {
	game.grid_size = grid_size;
	game.snake_speed = snake_speed;
	snake_init(10, 10, UP);
	apple_generate(grid_size, grid_size);
}

void game_end() {
	score = 0;
	snake_release();
	game_init(game.grid_size, game.snake_speed);
}

void game_update(double *last_time_frame, double current_time_frame) {
	if(current_time_frame > *last_time_frame + game.snake_speed) {
		snake_move();
		detect_apple(game.grid_size);
		if(detect_collision(game.grid_size)) {
			game_end();
		}
		*last_time_frame = current_time_frame;
	}
}


#endif // GAME_DEF_IMPLEMENTATION

#endif // GAME_DEF_H