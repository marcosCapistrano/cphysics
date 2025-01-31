#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "shape.h"

Shape Shape_newCircle(float radius)
{
    ShapeCircle *circle = malloc(sizeof(ShapeCircle));
    circle->radius = radius;

    Shape circle_shape = {
        .type = CIRCLE,
        .data = circle};

    return circle_shape;
}

Shape Shape_newBox(float width, float height)
{
    ShapeBox *box = malloc(sizeof(ShapeBox));
    box->width = width;
    box->height = height;

    Shape box_shape = {
        .type = BOX,
        .data = box};

    return box_shape;
}

void Shape_draw(Shape shape, Vector2 position, float rotation)
{
    if (shape.type == CIRCLE)
    {
        ShapeCircle *data = (ShapeCircle *)shape.data;
        DrawCircleLines(position.x, position.y, data->radius, GREEN);
        DrawLine(position.x, position.y, position.x + cos(rotation) * (data->radius), position.y - sin(rotation) * (data->radius), GREEN);
    }
    else if (shape.type == BOX)
    {
        ShapeBox *data = (ShapeBox *)shape.data;

        Rectangle rect;
        rect.x = position.x;
        rect.y = position.y;
        rect.width = data->width;
        rect.height = data->height;

        DrawRectanglePro(rect, (Vector2){.x = rect.width/2, .y=rect.height/2}, rotation, GREEN);
    }
}