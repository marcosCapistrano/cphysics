#ifndef PHYSICS_SHAPE_H
#define PHYSICS_SHAPE_H

#include "raymath.h"

typedef enum ShapeType
{
    SHAPE_CIRCLE,
    SHAPE_POLYGON
} ShapeType;

typedef struct Shape Shape;
struct Shape
{
    ShapeType type;
    float momentOfInertia;
    union
    {
        struct
        {
            float radius;
        } circle;

        struct
        {
            Vector2 vertices[4];
        } polygon;
    };
};

Shape *Shape_newCircle(float radius);
Shape *Shape_newBox(float width, float height);

void Shape_update(Shape *shape, Vector2 position, float rotation);

#endif