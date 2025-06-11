#ifndef BODY_H
#define BODY_H

#include "raymath.h"
#include "shape.h"

typedef struct Body Body;
struct Body
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

    Shape *shape;
};

Body Body_new(float x, float y, float mass);

void Body_setShapeCircle(Body *body, float radius);
void Body_setShapeBox(Body *body, float width, float height);

void Body_addForce(Body *particle, Vector2 force);
void Body_addTorque(Body *body, float torque);
void Body_integrate(Body *particle, float deltaTime);

#endif