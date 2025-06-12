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


    return shape;
}

Vector2 rotateVertice(Vector2 vertice, float rotation)
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

void Shape_updateVertices(Shape *shape, Vector2 position, float rotation)
{
    Vector2 rotatedVertices[4];
    rotatedVertices[0] = rotateVertice(shape->polygon.vertices[0], rotation);
    rotatedVertices[1] = rotateVertice(shape->polygon.vertices[1], rotation);
    rotatedVertices[2] = rotateVertice(shape->polygon.vertices[2], rotation);
    rotatedVertices[3] = rotateVertice(shape->polygon.vertices[3], rotation);

    shape->polygon.worldVertices[0] = Vector2Add(rotatedVertices[0], position);
    shape->polygon.worldVertices[1] = Vector2Add(rotatedVertices[1], position);
    shape->polygon.worldVertices[2] = Vector2Add(rotatedVertices[2], position);
    shape->polygon.worldVertices[3] = Vector2Add(rotatedVertices[3], position);
}

Vector2 Shape_edgeAt(Shape *shape, int verticeIndex)
{
    int nextVertice = verticeIndex+1;
    if(nextVertice > 3)
        nextVertice = 0;

    Vector2 vertice1 = shape->polygon.worldVertices[verticeIndex];
    Vector2 vertice2 = shape->polygon.worldVertices[nextVertice];

    return Vector2Subtract(vertice2, vertice1);
}

