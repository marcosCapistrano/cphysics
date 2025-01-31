#include "raylib.h"
#include "physics.h"
#include "body.h"

Body NewBody(float x, float y, float velx, float vely, float mass, float moment)
{
    Body newBody = {
        .position = Vector2Zero(),
        .velocity = Vector2Zero(),
        .acceleration = Vector2Zero(),
        .sumOfForces = Vector2Zero(),
        .sumOfTorques = 0,

        .mass = mass,
        .invMass = 1 / mass,
        .momentOfInertia = moment,
        .invMomentOfInertia = 1/moment,
    };

    newBody.position.x = x;
    newBody.position.y = y;
    newBody.velocity.x = velx;
    newBody.velocity.y = vely;

    newBody.rotation = 0;
    newBody.angularVelocity = 0;
    newBody.angularVelocity = 0;

    return newBody;
}

void Body_addForce(Body *body, Vector2 force)
{
    body->sumOfForces = Vector2Add(body->sumOfForces, force);
}

void Body_addTorque(Body *body, float torque)
{
    body->sumOfTorques = body->sumOfTorques + torque;
}

void Body_clearForces(Body *particle)
{
    particle->sumOfForces = Vector2Zero();
}

void Body_clearTorques(Body *body)
{
    body->sumOfTorques = 0;
}

void Body_integrate(Body *body, float deltaTime)
{
    //LINEAR
    body->acceleration.x = body->sumOfForces.x * PIXELS_PER_METER * body->invMass;
    body->acceleration.y = body->sumOfForces.y * PIXELS_PER_METER * body->invMass;

    body->velocity.x += body->acceleration.x * deltaTime;
    body->velocity.y += body->acceleration.y * deltaTime;

    body->position.x += body->velocity.x * deltaTime;
    body->position.y += body->velocity.y * deltaTime;

    //ANGULAR
    body->angularAcceleration += body->sumOfTorques + body->invMomentOfInertia;
    body->angularVelocity += body->angularAcceleration * deltaTime;
    body->rotation += body->angularVelocity *deltaTime;

    Body_clearForces(body);
    Body_clearTorques(body);
}

void Body_draw(Body *body)
{
    Shape_draw(body->shape, body->position, body->rotation);
}
