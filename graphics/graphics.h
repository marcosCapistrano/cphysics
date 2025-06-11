#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "raylib.h"

void Graphics_drawCircle(Vector2 position, float radius, float rotation);
void Graphics_drawPolygon(Vector2 position, Vector2 *vertices);

#endif