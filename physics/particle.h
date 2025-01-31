#ifndef PARTICLE_H
#define PARTICLE_H

#include "raymath.h"

typedef struct Particle
{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Vector2 sumOfForces;

    float mass;
    float invMass;
    float radius;
} Particle;

Particle NewParticle(float x, float y, float velx, float vely, float mass, float radius);

void ParticleAddForce(Particle *particle, Vector2 force);
void ParticleClearForces(Particle *particle);
void ParticleIntegrate(Particle *particle, float deltaTime);
void ParticleDraw(Particle *particle);

#endif