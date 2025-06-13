#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>
#include "collision.h"
#include "body.h"
#include "shape.h"

bool Physics_isCollidingCircleCircle(Body *a, Body *b, CollisionContact *contact)
{
    Shape *circleA = a->shape; // start
    Shape *circleB = b->shape; // end

    const Vector2 ab = Vector2Subtract(b->position, a->position);
    const float radiusSum = circleA->circle.radius + circleB->circle.radius;

    bool isColliding = Vector2Length(ab) < radiusSum;

    if (isColliding)
    {
        contact->a = a;
        contact->b = b;

        contact->normal = Vector2Normalize(ab);

        contact->start = Vector2Subtract(b->position, Vector2Scale(contact->normal, circleB->circle.radius));
        contact->end = Vector2Add(a->position, Vector2Scale(contact->normal, circleA->circle.radius));

        contact->depth = Vector2Length(Vector2Subtract(contact->end, contact->start));
    }

    return isColliding;
}

// Helper to project polygon vertices onto an axis
void projectPolygonOntoAxis(Vector2 *vertices, int count, Vector2 axis, float *min, float *max)
{
    *min = Vector2DotProduct(vertices[0], axis);
    *max = *min;

    for (int i = 1; i < count; i++)
    {
        float projection = Vector2DotProduct(vertices[i], axis);
        if (projection < *min) *min = projection;
        if (projection > *max) *max = projection;
    }
}

float findMinSeparation(Shape *aShape, Shape *bShape, Vector2 *axis, Vector2 *point)
{
    float separation = -FLT_MAX;

    // For each vertice 
    for (int i = 0; i < 4; i++)
    {
        // vertices for edge
        Vector2 va1 = aShape->polygon.worldVertices[i];
        Vector2 va2 = aShape->polygon.worldVertices[(i + 1) % 4];

        Vector2 edge = Vector2Subtract(va1, va2);
        Vector2 normal = Vector2Normalize((Vector2){-edge.y, edge.x});

        float minSeparation = FLT_MAX;
        Vector2 minVertex;
        for(int j = 0; j < 4; j++)
        {
            Vector2 vb = bShape->polygon.worldVertices[j];
            Vector2 vab = Vector2Subtract(vb, va1);
            float proj = Vector2DotProduct(vab, normal);
            if(proj < minSeparation)
            {
                minSeparation = proj;
                minVertex = vb;
            }
        }

        if(minSeparation > separation)
        {
            separation = minSeparation;

            (*axis).x = edge.x;
            (*axis).y = edge.y;

            (*point).x = minVertex.x;
            (*point).y = minVertex.y;
        }
    }
    return separation;
}

bool Physics_isCollidingBoxBox(Body *a, Body *b, CollisionContact *contact)
{
    Shape *aShape = a->shape;
    Shape *bShape = b->shape;

    Vector2 aAxis, bAxis;
    Vector2 aPoint, bPoint;

    float abSeparation = findMinSeparation(aShape, bShape, &aAxis, &aPoint);
    if(abSeparation >= 0)
    {
        return false;
    }

    float baSeparation = findMinSeparation(bShape, aShape, &bAxis, &bPoint);
    if(baSeparation >= 0)
    {
        return false;
    }

    (*contact).a = a;
    (*contact).b = b;

    if(abSeparation > baSeparation)
    {
        contact->depth = -abSeparation;
        contact->normal = Vector2Normalize((Vector2){-aAxis.y, aAxis.x});
        contact->start = aPoint;
        contact->end = Vector2Add(aPoint, Vector2Scale(contact->normal, contact->depth));
    }
    else
    {
        contact->depth = -baSeparation;
        contact->normal = Vector2Negate(Vector2Normalize((Vector2){-bAxis.y, bAxis.x}));
        contact->start = Vector2Subtract(bPoint, Vector2Scale(contact->normal, contact->depth));
        contact->end = bPoint;
    }

    return true;
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
