#ifndef BODY_H
#define BODY_H

#include "raymath.h"
#include "shape.h"

typedef struct Body
{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Vector2 sumOfForces;

    float mass;
    float invMass;
    float radius;

    Shape shape;
} Body;

Body NewBody(float x, float y, float velx, float vely, float mass);

void Body_addForce(Body *particle, Vector2 force);
void Body_clearForces(Body *particle);
void Body_integrate(Body *particle, float deltaTime);
void Body_draw(Body *particle);

#endif