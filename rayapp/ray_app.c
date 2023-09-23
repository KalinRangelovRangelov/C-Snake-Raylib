#include <stdio.h>
#include <raylib.h>

#include "snake.h"
#include "renderer_def.h"
#include "ray_renderer.h"
#include "game_def.h"
#include "consts.h"
#include "ray_texture_loader.h"

#define BACKGROUND_COLOR (Color) { 47, 100, 171, 255 }

void game_handle_input() {
	if     (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))	  snake_head->dir = UP;
	else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  snake_head->dir = DOWN;
	else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  snake_head->dir = LEFT;
	else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) snake_head->dir = RIGHT;
}


int main(void) {

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Snake");
	game.init(GRID_SIZE, SNAKE_SPEED);
	//texture_loader.load();
	
	
	double last_time_frame = GetTime();
	while(!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BACKGROUND_COLOR);
			game.handle_input();
			game.update(&last_time_frame, GetTime());
			renderer.draw(game.score, game.best_score); 	
		EndDrawing();
	}
	
	//texture_loader.unload();
}