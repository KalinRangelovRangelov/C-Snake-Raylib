#include <stdio.h>
#include <raylib.h>

#include "snake.h"
#include "game_def.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 850

#define GRID_SIZE 20
#define SCALE SCREEN_WIDTH / GRID_SIZE
#define START_X 0
#define START_Y SCREEN_HEIGHT - SCREEN_WIDTH

#define GRID_COLOR GRAY
#define SNAKE_COLOR LIGHTGRAY
#define APPLE_COLOR RED

#define SNAKE_SPEED 0.16f



void draw_grid() {
	for(size_t x = 0; x < SCREEN_WIDTH; ++x) {
		size_t x_scale = x * SCALE;
		DrawLine(x_scale, START_Y, x_scale, SCREEN_HEIGHT, GRAY);
	}

	for(size_t y = 0; y < SCREEN_HEIGHT; ++y) {
		size_t y_scale = y * SCALE + START_Y;
		DrawLine(START_X, y_scale, SCREEN_WIDTH, y_scale, GRID_COLOR);
	}
}

void draw_snake() {
	Snake *snake = snake_head;
	while(snake != NULL) {
		DrawRectangle(snake->x * SCALE + START_X, snake->y * SCALE + START_Y, SCALE, SCALE, SNAKE_COLOR);
		snake = snake->next;
	}
}

void draw_apple() {
	DrawRectangle(apple.x * SCALE + START_X, apple.y * SCALE + START_Y, SCALE, SCALE, APPLE_COLOR);
}

void draw_score() {
	char scoreText[80];
	sprintf(scoreText, "Score: %d", score);
	DrawText(scoreText, 20, 10, 20, BLACK);
}

void game_draw() {
	draw_grid();
	draw_apple();
	draw_snake();
	draw_score();
}

void game_handle_input() {
	if     (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))	  snake_head->dir = UP;
	else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  snake_head->dir = DOWN;
	else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  snake_head->dir = LEFT;
	else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) snake_head->dir = RIGHT;
}


int main(void) {
	game.init(GRID_SIZE, SNAKE_SPEED);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Snake");
	
	double last_time_frame = GetTime();
	while(!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);
			game.handle_input();
			game.update(&last_time_frame, GetTime());
			game.draw(); 			
			
		EndDrawing();
	}
}