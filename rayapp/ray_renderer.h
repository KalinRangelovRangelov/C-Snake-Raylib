#ifndef RAY_RENDERER_H
#define RAY_RENDERER_H

#include <string.h>
#include <raylib.h>

#include "../snake.h"
#include "../consts.h"
#include "ray_texture_loader.h"

#define GRID_COLOR LIGHTGRAY
#define SNAKE_COLOR GREEN
#define APPLE_COLOR RED
#define SCORE_COLOR GREEN
#define BEST_SCORE_COLOR YELLOW



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
	//Vector2 pos = {x, y};
	//DrawTextureEx(texture_loader.apple, pos, 0, texture_loader.apple_scale, WHITE);
	DrawRectangle(x, y, SCALE, SCALE, APPLE_COLOR);
}

void draw_score(int score, int best_score) {
	char score_text[17];
	sprintf(score_text, "Score: %d", score);
	DrawText(score_text, GRID_OFFSET, 15, 20, SCORE_COLOR);
	
	char best_text[17];
	sprintf(best_text, "Best: %d", best_score);
	size_t best_count = strlen(best_text);
	size_t x = SCREEN_WIDTH - GRID_OFFSET - (best_count * 15);
	DrawText(best_text, x, 15, 20, BEST_SCORE_COLOR);
}

void renderer_draw(int score, int best_score) {
	draw_grid();
	draw_apple();
	draw_snake();
	draw_score(score, best_score);
}

#endif // RAY_RENDERER_H