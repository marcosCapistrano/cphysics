#ifndef FORCE_H
#define FORCE_H

#include "raymath.h"

Vector2 Force_newGravityForce(float ms);
Vector2 Force_newDragForce(Vector2 velocity, float k);
Vector2 Force_newSpringForce(Vector2 position, Vector2 anchor, float restLength, float k);
void Force_springDraw(Vector2 position, Vector2 anchor, float restLength, float k);

#endif