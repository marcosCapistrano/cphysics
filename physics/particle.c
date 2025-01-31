#include "raylib.h"
#include "physics.h"
#include "particle.h"

Particle NewParticle(float x, float y, float velx, float vely, float mass, float radius)
{
    Particle newParticle = {
        .position = Vector2Zero(),
        .velocity = Vector2Zero(),
        .acceleration = Vector2Zero(),
        .sumOfForces = Vector2Zero(),

        .mass = mass,
        .invMass = 1 / mass,
        .radius = radius,
    };

    newParticle.position.x = x;
    newParticle.position.y = y;
    newParticle.velocity.x = velx;
    newParticle.velocity.y = vely;

    return newParticle;
}

void ParticleAddForce(Particle *particle, Vector2 force)
{
    particle->sumOfForces = Vector2Add(particle->sumOfForces, force);
}

void ParticleClearForces(Particle *particle)
{
    particle->sumOfForces = Vector2Zero();
}

void ParticleIntegrate(Particle *particle, float deltaTime)
{
    particle->acceleration.x = particle->sumOfForces.x * PIXELS_PER_METER * particle->invMass;
    particle->acceleration.y = particle->sumOfForces.y * PIXELS_PER_METER * particle->invMass;

    particle->velocity.x += particle->acceleration.x * deltaTime;
    particle->velocity.y += particle->acceleration.y * deltaTime;

    particle->position.x += particle->velocity.x * deltaTime;
    particle->position.y += particle->velocity.y * deltaTime;

    ParticleClearForces(particle);
}

void ParticleDraw(Particle *particle)
{
    DrawCircle(particle->position.x, particle->position.y, particle->radius, RED);
}
