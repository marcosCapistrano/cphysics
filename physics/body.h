#ifndef BODY_H
#define BODY_H

#include "raymath.h"
#include "shape.h"

typedef struct Body
{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    float rotation;
    float angularVelocity;
    float angularAcceleration;

    Vector2 sumOfForces;
    float sumOfTorques;

    float mass;
    float invMass;
    float momentOfInertia;
    float invMomentOfInertia;

    Shape shape;
} Body;

Body NewBody(float x, float y, float velx, float vely, float mass, float moment);

void Body_addForce(Body *particle, Vector2 force);
void Body_addTorque(Body *body, float torque);
void Body_clearForces(Body *particle);
void Body_integrate(Body *particle, float deltaTime);
void Body_draw(Body *particle);

#endif