#ifndef RAY_RENDERER_H
#define RAY_RENDERER_H

#include <raylib.h>

#include "../snake.h"
#include "../consts.h"

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

void renderer_draw() {
	draw_grid();
	draw_apple();
	draw_snake();
	draw_score();
}

#endif // RAY_RENDERER_H