#ifndef RAY_TEXTURE_LOADER_H
#define RAY_TEXTURE_LOADER_H

#include "consts.h"

void texture_loader_load();
void texture_loader_unload();

typedef struct {
	Texture2D apple;
	float apple_scale;
	
	void (*load)();
	void (*unload)();
} TextureLoader;

TextureLoader texture_loader = {
	.load = texture_loader_load, 
	.unload = texture_loader_unload
};


void texture_loader_load() {
	Image image = LoadImage("sprites/apple_0.png");     // Loaded in CPU memory (RAM)
	Texture2D appleTexture = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
	UnloadImage(image); 
	texture_loader.apple = appleTexture;
	texture_loader.apple_scale = ((float)SCALE + 10) / (float)appleTexture.width;
}

void texture_loader_unload() {
	UnloadTexture(texture_loader.apple);
}

#endif // RAY_TEXTURE_LOADER_H