#ifndef RENDERER_DEF_H
#define RENDERER_DEF_H

void renderer_draw(int score, int best_score);


typedef struct {
	void (*draw)(int score, int best_score);
} Renderer;

Renderer renderer = {	
	.draw = renderer_draw	
};


#endif // RENDERER_DEF_H