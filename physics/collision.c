#include <stdio.h>
#include <stdbool.h>
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