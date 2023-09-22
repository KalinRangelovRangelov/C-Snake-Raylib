#ifndef PARTICLES_H
#define PARTICLES_H

#include <raylib.h>

#define MAX_PARTICLES 10

typedef struct {
	Vector2 position;
	Vector2 velocity;
	Color color;
	int lifetime;
	bool active;
} Particle;

Particle particles[MAX_PARTICLES];


void particles_init(Particle *particle, Vector2 position, Vector2 velocity, Color color, int lifetime) {
	particle->position = position;
	particle->velocity = velocity;
	particle->color = color;
	particle->lifetime = lifetime;
	particle->active = true; // Mark the particle as active
}

void particles_spawn(Vector2 position, int numParticlesToSpawn) {
	for (int i = 0; i < numParticlesToSpawn; i++) {
	    for (int j = 0; j < MAX_PARTICLES; j++) {
	        if (!particles[j].active) {
	            // Initialize a new particle
	            Vector2 velocity = (Vector2){ GetRandomValue(-10, 10), GetRandomValue(-10, 10) };
	            Color color = RED; // Customize the color
	            int lifetime = 10; // Adjust the lifetime as needed
	            particles_init(&particles[j], position, velocity, color, lifetime);
	            break;
	        }
	    }
	}
}

void particles_party() {
	for (int i = 0; i < MAX_PARTICLES; i++) {
	    if (particles[i].active) {
	        particles[i].position.x += particles[i].velocity.x;
	        particles[i].position.y += particles[i].velocity.y;
	        particles[i].lifetime--;

	        if (particles[i].lifetime <= 0) {
	            particles[i].active = false; // Deactivate the particle
	        }
	    }
	}
}

void particles_draw() {
	for (int i = 0; i < MAX_PARTICLES; i++) {
	    if (particles[i].active) {
	        //DrawPixelV(particles[i].position, particles[i].color);
			DrawRectangle(particles[i].position.x, particles[i].position.y, 10, 10, particles[i].color);
	    }
	}
}

#endif // PARTICLES_H