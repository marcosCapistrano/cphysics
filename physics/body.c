#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "physics.h"
#include "body.h"

Body Body_new(float x, float y, float mass)
{
    Body newBody = {0};
    newBody.mass = mass;
    newBody.invMass = 1.0f / mass;

    newBody.position.x = x;
    newBody.position.y = y;

    newBody.shape = NULL;

    return newBody;
}

void Body_setShapeCircle(Body *body, float radius)
{
    Shape *shape = Shape_newCircle(radius);
    body->shape = shape;

    float I = shape->momentOfInertia * body->mass;
    body->momentOfInertia = I;
    body->invMomentOfInertia = 1.0f/I;

    printf("Moment circle: %f\n", body->momentOfInertia);
    printf("InvMoment circle: %f\n", body->invMomentOfInertia);
}

void Body_setShapeBox(Body *body, float width, float height)
{
    Shape *shape = Shape_newBox(width, height);
    body->shape = shape;

    float I = shape->momentOfInertia * body->mass;
    body->momentOfInertia = I;
    body->invMomentOfInertia = 1.0f/I;

    printf("Moment box: %f\n", body->momentOfInertia);
    printf("InvMoment box: %f\n", body->invMomentOfInertia);
}

void Body_addForce(Body *body, Vector2 force)
{
    body->sumOfForces = Vector2Add(body->sumOfForces, force);
}

void Body_addTorque(Body *body, float torque)
{
    body->sumOfTorques = body->sumOfTorques + torque;
}

void Body_integrate(Body *body, float deltaTime)
{
    // LINEAR
    body->acceleration.x = body->sumOfForces.x * PIXELS_PER_METER * body->invMass;
    body->acceleration.y = body->sumOfForces.y * PIXELS_PER_METER * body->invMass;

    body->velocity.x += body->acceleration.x * deltaTime;
    body->velocity.y += body->acceleration.y * deltaTime;

    body->position.x += body->velocity.x * deltaTime;
    body->position.y += body->velocity.y * deltaTime;

    // ANGULAR
    body->angularAcceleration += body->sumOfTorques * body->invMomentOfInertia;
    body->angularVelocity += body->angularAcceleration * deltaTime;
    body->rotation += body->angularVelocity * deltaTime;

    // Clear force and torque
    body->sumOfForces = Vector2Zero();
    body->sumOfTorques = 0;
}