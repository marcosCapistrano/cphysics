#include <stdio.h>
#include <math.h>
#include "graphics.h"
#include "raylib.h"
#include "raymath.h"


void Graphics_drawCircle(Vector2 position, float radius, float rotation)
{
    DrawCircle(position.x, position.y, radius, GREEN);
    DrawLine(position.x, position.y, position.x + (radius * cos(DEG2RAD * rotation)), position.y + (radius * sin(DEG2RAD * rotation)), BLACK);
}

void Graphics_drawPolygon(Vector2 position, Vector2 *worldVertices, float rotation, Color color)
{
    Vector2 vertices[6];
    vertices[0] = position;
    vertices[1] = worldVertices[0]; // top-left
    vertices[2] = worldVertices[3]; // bottom-left
    vertices[3] = worldVertices[2];  // bottom-right
    vertices[4] = worldVertices[1]; // top-right
    vertices[5] = worldVertices[0]; // top-left

    DrawTriangleFan(vertices, 6, color);
}