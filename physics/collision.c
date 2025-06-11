#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "collision.h"
#include "body.h"
#include "shape.h"

bool Physics_isCollidingCircleCircle(Body *a, Body *b, CollisionContact *contact)
{
    Shape *circleA = a->shape; //start
    Shape *circleB = b->shape; //end

    const Vector2 ab = Vector2Subtract(b->position, a->position);
    const float radiusSum = circleA->circle.radius + circleB->circle.radius;

    bool isColliding = Vector2Length(ab) < radiusSum;

    if(isColliding)
    {
        contact->a = a;
        contact->b = b;

        contact->normal = Vector2Normalize(ab);
        printf("normal: %f %f\n", contact->normal.x, contact->normal.y);
        
        contact->start = Vector2Subtract(b->position, Vector2Scale(contact->normal, circleB->circle.radius));
        contact->end = Vector2Add(a->position, Vector2Scale(contact->normal, circleA->circle.radius));

        contact->depth = Vector2Length(Vector2Subtract(contact->end, contact->start));
    }   

    return isColliding;
}

void Physics_resolvePenetration(CollisionContact *contact)
{
    Body *a = contact->a;
    Body *b = contact->b;

    float da = contact->depth / (a->invMass + b->invMass) * a->invMass;
    float db = contact->depth / (a->invMass + b->invMass) * b->invMass;

    a->position = Vector2Subtract(a->position, Vector2Scale(contact->normal, da));
    b->position = Vector2Add(b->position, Vector2Scale(contact->normal, db));
}

void Physics_resolveCollision(CollisionContact *contact)
{
    Physics_resolvePenetration(contact);

    Body *a = contact->a;
    Body *b = contact->b;

    float e = fmin(a->restitution, b->restitution);

    const Vector2 vrel = Vector2Subtract(a->velocity, b->velocity);
    const float vrelDotNormal = Vector2DotProduct(vrel, contact->normal);

    const Vector2 impulseDirection = contact->normal;
    const float impulseMagnitude = -(1 + e) * vrelDotNormal / (a->invMass + b->invMass);

    const Vector2 j = Vector2Scale(impulseDirection, impulseMagnitude);

    Body_applyImpulse(a, j);
    Body_applyImpulse(b, Vector2Negate(j));

}
