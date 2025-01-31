#include "raylib.h"
#include "physics.h"
#include "body.h"

Body NewBody(float x, float y, float velx, float vely, float mass)
{
    Body newBody = {
        .position = Vector2Zero(),
        .velocity = Vector2Zero(),
        .acceleration = Vector2Zero(),
        .sumOfForces = Vector2Zero(),

        .mass = mass,
        .invMass = 1 / mass,
    };

    newBody.position.x = x;
    newBody.position.y = y;
    newBody.velocity.x = velx;
    newBody.velocity.y = vely;

    return newBody;
}

void Body_addForce(Body *body, Vector2 force)
{
    body->sumOfForces = Vector2Add(body->sumOfForces, force);
}

void Body_clearForces(Body *particle)
{
    particle->sumOfForces = Vector2Zero();
}

void Body_integrate(Body *particle, float deltaTime)
{
    particle->acceleration.x = particle->sumOfForces.x * PIXELS_PER_METER * particle->invMass;
    particle->acceleration.y = particle->sumOfForces.y * PIXELS_PER_METER * particle->invMass;

    particle->velocity.x += particle->acceleration.x * deltaTime;
    particle->velocity.y += particle->acceleration.y * deltaTime;

    particle->position.x += particle->velocity.x * deltaTime;
    particle->position.y += particle->velocity.y * deltaTime;

    Body_clearForces(particle);
}

void Body_draw(Body *body)
{
    Shape_draw(body->position, body->shape);
}
