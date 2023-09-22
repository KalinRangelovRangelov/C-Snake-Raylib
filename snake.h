#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	UP, 
	DOWN, 
	LEFT, 
	RIGHT
} DIR;

typedef struct {
	int x; 
	int y;
} Apple;

typedef struct snake {
	int x; 
	int y; 
	DIR dir;

	struct snake *next;
} Snake;

Snake *snake_head;
Apple apple;
int score = 0;

void snake_init(int x, int y, DIR dir);
void snake_release();
void snake_move();
void snake_grow();
bool snake_detect_apple();
bool snake_detect_body_collision();
void apple_generate(int max_x, int max_y);
void detect_apple(int grid_size);


void snake_init(int x, int y, DIR dir) {
	snake_head = malloc(sizeof(Snake));
	snake_head->x = x;
	snake_head->y = y;
	snake_head->dir = dir;
	snake_head->next = NULL;
}

void snake_release() {
	Snake *snake = snake_head;
	while(snake != NULL) {
		Snake *segment = snake;
		snake = snake->next;
		free(segment);
	}
}

void snake_move() {
	Snake *snake = snake_head;
	int save_x = snake->x;
	int save_y = snake->y; 
	DIR save_dir = snake->dir;
	
	switch(snake->dir) {
		case UP: 	snake->y--; break; 
		case DOWN: 	snake->y++; break; 
		case LEFT: 	snake->x--; break; 
		case RIGHT: snake->x++; break;
	}
	
	while(snake->next != NULL) {
		int x = snake->next->x; 
		int y = snake->next->y;
		DIR dir = snake->next->dir;	
		
		snake = snake->next;
		snake->x = save_x;
		snake->y = save_y;
		snake->dir = save_dir;
		
		save_x = x;
		save_y = y;
		save_dir = dir;
	}
}

void snake_grow() {
	int save_x;
	int save_y;
	DIR save_dir;

	Snake *snake = snake_head;
	while(snake != NULL) {
		save_x = snake->x;
		save_y = snake->y;
		save_dir = snake->dir;
		snake = snake->next;
	}
	
	switch(save_dir) {
		case UP: 	save_y++; break;
		case DOWN: 	save_y--; break;
		case LEFT: 	save_x++; break;
		case RIGHT: save_x--; break;
	}
	
	snake = snake_head;
	while(snake->next != NULL) {
		snake = snake->next;
	}
	
	Snake *newSegment = malloc(sizeof(Snake));
	newSegment->x = save_x; 
	newSegment->y = save_y; 
	newSegment->dir = save_dir; 
	snake->next = newSegment;
}

bool snake_detect_apple() {
	return apple.x == snake_head->x && 
		   apple.y == snake_head->y;
}

bool detect_collision(int grid_size) {
	// Grid collision
	if(snake_head->x < 0 || snake_head->y < 0  || snake_head->x >= grid_size || snake_head->y >= grid_size) {
		return true;
	}
	
	// Snake collision
	if(snake_detect_body_collision()) {
		return true;
	}
	return false;
}


bool snake_detect_body_collision() {
	Snake *snake = snake_head->next;
	while(snake != NULL) {
		if(snake->x == snake_head->x && snake->y == snake_head->y) {
			return true;
		}
		snake = snake->next;
	}
	return false;
}

bool is_position_in_snake(int x, int y) {
	Snake *snake = snake_head;
	while(snake != NULL) {
		if(snake->x == x && snake->y == y) {
			return true;
		}
		snake = snake->next;
	}
	return false;
}

void apple_generate(int max_x, int max_y) {
	bool found_valid_position = false;
	while(!found_valid_position) {
		int x = rand() % max_x;
		int y = rand() % max_y;
		if(!is_position_in_snake(x, y)) {
			apple.x = x;
			apple.y = y;
			found_valid_position = true;
		}
	}
}

void detect_apple(int grid_size) {
	if(snake_detect_apple()) {
		snake_grow();
		apple_generate(grid_size, grid_size);
		score++;
	}
}

#endif // SNAKE_H