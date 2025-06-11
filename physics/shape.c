#include <stdlib.h>
#include <stdio.h>
#include "shape.h"

Vector2 updateVertice(Vector2 vertice, float rotation);

Shape *Shape_newCircle(float radius)
{
    Shape *shape = malloc(sizeof(Shape));
    shape->type = SHAPE_CIRCLE;
    shape->circle.radius = radius;

    shape->momentOfInertia = radius * radius * 0.5;
    printf("moment: %f\n", shape->momentOfInertia);

    return shape;
}

Shape *Shape_newBox(float width, float height)
{
    Shape *shape = malloc(sizeof(Shape));
    shape->type = SHAPE_POLYGON;

    shape->polygon.vertices[0] = (Vector2){-width / 2, -height / 2}; // top left
    shape->polygon.vertices[1] = (Vector2){width / 2, -height / 2};  // top right
    shape->polygon.vertices[2] = (Vector2){width / 2, height / 2};   // bottom right
    shape->polygon.vertices[3] = (Vector2){-width / 2, height / 2};  // bottom left

    shape->momentOfInertia = 0.083333f * ((width * width) + (height * height));

    printf("moment: %f\n", shape->momentOfInertia);

    return shape;
}

void Shape_update(Shape *shape, Vector2 position, float rotation)
{
    if (shape->type == SHAPE_POLYGON)
    {
        shape->polygon.vertices[0] = updateVertice(shape->polygon.vertices[0], rotation);
        shape->polygon.vertices[1] = updateVertice(shape->polygon.vertices[1], rotation);
        shape->polygon.vertices[2] = updateVertice(shape->polygon.vertices[2], rotation);
        shape->polygon.vertices[3] = updateVertice(shape->polygon.vertices[3], rotation);
    }
}

Vector2 updateVertice(Vector2 vertice, float rotation)
{
    // Apply rotation (in radians)
    float rad = rotation * DEG2RAD;
    float cosR = cosf(rad);
    float sinR = sinf(rad);

    Vector2 rotated = {
        vertice.x * cosR - vertice.y * sinR,
        vertice.x * sinR + vertice.y * cosR};

    return rotated;
}
