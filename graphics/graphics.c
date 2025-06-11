#include <math.h>
#include "graphics.h"
#include "raymath.h"

void Graphics_drawCircle(Vector2 position, float radius, float rotation)
{
    DrawCircle(position.x, position.y, radius, GREEN);
    DrawLine(position.x, position.y, position.x + (radius * cos(DEG2RAD * rotation)), position.y + (radius * sin(DEG2RAD * rotation)), BLACK);
}

void Graphics_drawPolygon(Vector2 position, Vector2 *vertices)
{
    Vector2 worldVertices[6];
    worldVertices[0] = position;
    worldVertices[1] = Vector2Add(vertices[0], position); // top-left
    worldVertices[2] = Vector2Add(vertices[3], position); // bottom-left
    worldVertices[3] = Vector2Add(vertices[2], position); // bottom-right
    worldVertices[4] = Vector2Add(vertices[1], position); // top-right
    worldVertices[5] = Vector2Add(vertices[0], position); // top-left

    DrawTriangleFan(worldVertices, 6, GREEN);

    // for (int i = 0; i < 5; i++)
    // {
    //     DrawCircleV(worldVertices[i], 4, RED);
    // }
}