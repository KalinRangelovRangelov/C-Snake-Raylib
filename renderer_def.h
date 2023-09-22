#ifndef RENDERER_DEF_H
#define RENDERER_DEF_H

void renderer_draw();


typedef struct {
	void (*draw)();
} Renderer;

Renderer renderer = {	
	.draw = renderer_draw	
};


#endif // RENDERER_DEF_H