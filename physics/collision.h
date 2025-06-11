#ifndef COLLISION_H
#define COLLISION_H

#include "body.h"

typedef struct CollisionContact CollisionContact;
struct CollisionContact
{
    Body *a;
    Body *b;

    Vector2 start;
    Vector2 end;

    Vector2 normal;
    float depth;
};

bool Physics_isCollidingCircleCircle(Body *a, Body *b, CollisionContact *contact);
void Physics_resolveCollision(CollisionContact *contact);

#endif