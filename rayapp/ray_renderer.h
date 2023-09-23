#ifndef RAY_RENDERER_H
#define RAY_RENDERER_H

#include <string.h>
#include <raylib.h>

#include "../snake.h"
#include "../consts.h"
#include "ray_texture_loader.h"
#include "particles.h"

#define GRID_COLOR LIGHTGRAY
#define SNAKE_COLOR (Color) { 98, 231, 60, 255 } // GREEN
#define APPLE_COLOR (Color) { 217, 56, 51, 255 } // RED
#define SCORE_COLOR SNAKE_COLOR
#define BEST_SCORE_COLOR YELLOW


int get_world_position(int p) {
	return p * SCALE + GRID_OFFSET;
}

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

void draw_snake_head_at(int x, int y, DIR dir) {
	int radius		  = SCALE_HALF;
	int segments	  = 10;
	int center_x      = x + SCALE_HALF;
	int center_y 	  = y + SCALE;
	float start_angle = 270;
	float end_angle	  = 90;
	
	switch(dir) {
	case UP: 
		center_x 	= x + SCALE_HALF;
		center_y 	= y + SCALE;
		start_angle = 270;
		end_angle	= 90;
		break;
	case DOWN:
		center_x 	= x + SCALE_HALF;
		center_y 	= y;
		start_angle = -90;
		end_angle 	= 90;
		break;
	case LEFT:
		center_x 	= x + SCALE;
		center_y 	= y + SCALE_HALF;
		start_angle = 0;
		end_angle 	= -180;
		break;
	case RIGHT:
		center_x 	= x;
		center_y 	= y + SCALE_HALF;
		start_angle = 0;
		end_angle 	= 180;
		break;
	}
	
	Vector2 center 	 = { center_x, center_y };
	
	printf("x: %d, y: %d, cx: %d, cy: %d, hc: %d, r: %d\n", x, y, center_x, center_y, SCALE_HALF, radius);

	DrawCircleSector(center, radius, start_angle, end_angle, segments, SCORE_COLOR);
}

void draw_snake() {
	Snake *snake = snake_head;
	while(snake != NULL) {
		int x = get_world_position(snake->x);
		int y = get_world_position(snake->y);
		
		if(snake == snake_head) {
			draw_snake_head_at(x, y, snake->dir);
		}
		else {
			DrawRectangle(x, y, SCALE, SCALE, SNAKE_COLOR);
		}
		
		snake = snake->next;
	}
}

void draw_apple() {
	int x = get_world_position(apple.x);
	int y = get_world_position(apple.y);
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
	particles_draw();
}

#endif // RAY_RENDERER_H