#ifndef SHAPE_H
#define SHAPE_H

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
    float angle;
} ShapeCircle;

typedef struct ShapeBox {
    float width, height;
} ShapeBox;

typedef struct ShapePolygon {
    float *points;
    int point_count;
} ShapePolygon;

Shape Shape_newCircle(float radius, float angle);
Shape Shape_newBox(float width, float height);

void Shape_draw(Vector2 position, Shape shape);

#endif