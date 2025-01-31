#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "shape.h"

Shape Shape_newCircle(float radius, float angle)
{
    ShapeCircle *circle = malloc(sizeof(ShapeCircle));
    circle->radius = radius;
    circle->angle = angle;

    Shape circle_shape = {
        .type = CIRCLE,
        .data = circle};

    return circle_shape;
}

Shape Shape_newBox(float width, float height)
{
    ShapeBox *box = malloc(sizeof(ShapeBox));
    box->width = 10.0f;
    box->height = 8.0f;

    Shape box_shape = {
        .type = BOX,
        .data = box};

    return box_shape;
}

void Shape_draw(Vector2 position, Shape shape)
{
    if (shape.type == CIRCLE)
    {
        ShapeCircle *data = (ShapeCircle *)shape.data;
        DrawCircleLines(position.x, position.y, data->radius, GREEN);
        DrawLine(position.x, position.y, position.x + cos(data->angle)*(data->radius), position.y - sin(data->angle)*(data->radius), GREEN);
    }
}