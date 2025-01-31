#ifndef SHAPE_H
#define SHAPE_H

#include "raymath.h"

typedef enum ShapeType {
    CIRCLE,
    BOX,
    POLYGON,
} ShapeType;

typedef struct Shape {
    ShapeType type; 
    void *data;
    bool (*check_collision) (void *shape1, void *shape2);
} Shape;

typedef struct ShapeCircle {
    float radius; 
} ShapeCircle;

typedef struct ShapeBox {
    float width;
    float height;
} ShapeBox;

typedef struct ShapePolygon {
    float *points;
    int point_count;
} ShapePolygon;

Shape Shape_newCircle(float radius);
Shape Shape_newBox(float width, float height);

void Shape_draw(Shape shape, Vector2 position, float rotation);

#endif