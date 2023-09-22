#ifndef PARTICLES_H
#define PARTICLES_H

#include <raylib.h>


#define MAX_PARTICLES 10
#define PARTICLES_LIFETIME 5
#define PARTICLES_SIZE 10
#define PARTICLES_VELOCITY 10

Color particle_colors[12] = {
	GOLD, ORANGE, PINK, MAROON, RED, LIME, SKYBLUE, BLUE, PURPLE, VIOLET, YELLOW, MAGENTA
};

// ChatGPT generated code

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
	            Vector2 velocity = (Vector2) { 
					GetRandomValue(-PARTICLES_VELOCITY, PARTICLES_VELOCITY), 
					GetRandomValue(-PARTICLES_VELOCITY, PARTICLES_VELOCITY) 
				};
	            Color color = particle_colors[rand() % 12];
	            int lifetime = PARTICLES_LIFETIME; // Adjust the lifetime as needed
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
			DrawRectangle(particles[i].position.x, particles[i].position.y, PARTICLES_SIZE, PARTICLES_SIZE, particles[i].color);
	    }
	}
}

#endif // PARTICLES_H