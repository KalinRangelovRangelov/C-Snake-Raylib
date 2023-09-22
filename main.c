#include <stdio.h>
#include <raylib.h>

#include "snake.h"

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

void init_game() {
	snake_init(10, 10, UP);
	apple_generate(GRID_SIZE, GRID_SIZE);
}

void end_game() {
	score = 0;
	snake_release();
	init_game();
}

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

void draw() {
	draw_grid();
	draw_apple();
	draw_snake();
}

void detect_apple() {
	if(snake_detect_apple()) {
		snake_grow();
		apple_generate(GRID_SIZE, GRID_SIZE);
		score++;
	}
}

void detect_collision() {
	// Grid collision
	if(snake_head->x < 0 || snake_head->y < 0  || snake_head->x >= GRID_SIZE || snake_head->y >= GRID_SIZE) {
		end_game();
	}
	
	// Snake collision
	if(snake_detect_body_collision()) {
		end_game();
	}
}

void update(double *last_time_frame) {
	double time_frame = GetTime();
	if(time_frame > *last_time_frame + SNAKE_SPEED) {
		snake_move();
		detect_apple();
		detect_collision();
		*last_time_frame = time_frame;
	}
}

void handle_input() {
	if     (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))	  snake_head->dir = UP;
	else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  snake_head->dir = DOWN;
	else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  snake_head->dir = LEFT;
	else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) snake_head->dir = RIGHT;
}


int main(void) {
	
	init_game();
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
	
	double last_time_frame = GetTime();
	while(!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);
			char scoreText[80];
			sprintf(scoreText, "Score: %d", score);
			DrawText(scoreText, 20, 10, 20, BLACK);
			
			draw(); 
			update(&last_time_frame);
			handle_input();
			
		EndDrawing();
	}
}