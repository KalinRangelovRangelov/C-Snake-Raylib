#ifndef RAY_RENDERER_H
#define RAY_RENDERER_H

#include <raylib.h>

#include "../snake.h"
#include "../consts.h"
#include "ray_texture_loader.h"

#define GRID_COLOR LIGHTGRAY
#define SNAKE_COLOR GREEN
#define APPLE_COLOR RED
#define SCORE_COLOR GREEN



void draw_grid() {
	
	/*for(size_t x = 0; x <= GRID_SIZE; x++) {
		size_t x_scale = x * SCALE + GRID_OFFSET;
		DrawLine(x_scale, GRID_OFFSET, x_scale, SCREEN_HEIGHT - GRID_OFFSET, GRID_COLOR);
	}

	for(size_t y = 0; y <= GRID_SIZE; ++y) {
		size_t y_scale = y * SCALE + GRID_OFFSET;
		DrawLine(GRID_OFFSET, y_scale, SCREEN_WIDTH - GRID_OFFSET, y_scale, GRID_COLOR);
	} */
	
	Rectangle frame = { GRID_OFFSET, GRID_OFFSET, SCREEN_WIDTH - (2 * GRID_OFFSET), SCREEN_HEIGHT - (2 * GRID_OFFSET) };
	DrawRectangleLinesEx(frame, 1.5, GRID_COLOR);
}

void draw_snake() {
	Snake *snake = snake_head;
	while(snake != NULL) {
		DrawRectangle(snake->x * SCALE + GRID_OFFSET, snake->y * SCALE + GRID_OFFSET, SCALE, SCALE, SNAKE_COLOR);
		snake = snake->next;
	}
}

void draw_apple() {
	int x = apple.x * SCALE + GRID_OFFSET;
	int y = apple.y * SCALE + GRID_OFFSET;
	Vector2 pos = {x, y};
	DrawTextureEx(texture_loader.apple, pos, 0, texture_loader.apple_scale, WHITE);
}

void draw_score() {
	char scoreText[80];
	sprintf(scoreText, "Score: %d", score);
	DrawText(scoreText, 20, 10, 20, SCORE_COLOR);
}

void renderer_draw() {
	draw_grid();
	draw_apple();
	draw_snake();
	draw_score();
}

#endif // RAY_RENDERER_H