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


void snake_init(int x, int y, DIR dir) {
	snake_head = malloc(sizeof(Snake));
	snake_head->x = x;
	snake_head->y = y;
	snake_head->dir = dir;
	snake_head->next = NULL;
}

void snake_release() {
	Snake *track = snake_head;
	while(track != NULL) {
		Snake *segment = track;
		track = track->next;
		free(segment);
	}
}

void snake_move() {
	Snake *track = snake_head;
	int save_x = track->x;
	int save_y = track->y; 
	DIR save_dir = track->dir;
	
	switch(track->dir) {
		case UP: 	track->y--; break; 
		case DOWN: 	track->y++; break; 
		case LEFT: 	track->x--; break; 
		case RIGHT: track->x++; break;
	}
	
	while(track->next != NULL) {
		int x = track->next->x; 
		int y = track->next->y;
		DIR dir = track->next->dir;	
		
		track = track->next;
		track->x = save_x;
		track->y = save_y;
		track->dir = save_dir;
		
		save_x = x;
		save_y = y;
		save_dir = dir;
	}
}

void snake_grow() {
	int save_x;
	int save_y;
	DIR save_dir;

	Snake *track = snake_head;
	while(track != NULL) {
		save_x = track->x;
		save_y = track->y;
		save_dir = track->dir;
		track = track->next;
	}
	
	switch(save_dir) {
		case UP: 	save_y++; break;
		case DOWN: 	save_y--; break;
		case LEFT: 	save_x++; break;
		case RIGHT: save_x--; break;
	}
	
	track = snake_head;
	while(track->next != NULL) {
		track = track->next;
	}
	
	Snake *newSegment = malloc(sizeof(Snake));
	newSegment->x = save_x; 
	newSegment->y = save_y; 
	newSegment->dir = save_dir; 
	track->next = newSegment;
}

bool snake_detect_apple() {
	return apple.x == snake_head->x && 
		   apple.y == snake_head->y;
}

bool snake_detect_body_collision() {
	Snake *track = snake_head->next;
	while(track != NULL) {
		if(track->x == snake_head->x && track->y == snake_head->y) {
			return true;
		}
		track = track->next;
	}
	return false;
}

void apple_generate(int max_x, int max_y) {
	apple.x = rand() % max_x;
	apple.y = rand() % max_y;
}



#endif // SNAKE_H