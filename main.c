#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#include "physics/body.h"
#include "physics/force.h"
#include "physics/collision.h"
#include "graphics/graphics.h"

const int screenWidth = 800;
const int screenHeight = 600;

Body box1;
Body box2;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    box1 = Body_new(200, 200, 50.0f);
    Body_setShapeBox(&box1, 60, 60);

    box2 = Body_new(250, 250, 50.0f);
    Body_setShapeBox(&box2, 60, 60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_A))
            box2.rotation += 30.0f * deltaTime;
        
        if (IsKeyDown(KEY_D))
            box1.rotation += 30.0f * deltaTime;


        box2.position.x = GetMouseX();
        box2.position.y = GetMouseY();

        Shape_updateVertices(box1.shape, box1.position, box1.rotation);
        Shape_updateVertices(box2.shape, box2.position, box2.rotation);

        /*
            CollisionContact contact;
            if(Physics_isColliding...)
            {
                Physics_resolveCollision(&contact);
            }
        */

        BeginDrawing();
        {
            ClearBackground(BLACK);

            CollisionContact contact;
            Graphics_drawPolygon(box1.position, box1.shape->polygon.worldVertices, box1.rotation, GREEN);
            Graphics_drawPolygon(box2.position, box2.shape->polygon.worldVertices, box2.rotation, GREEN);

            if (Physics_isCollidingBoxBox(&box1, &box2, &contact))
            {
                DrawCircle(contact.start.x, contact.start.y, 5, RED);
                DrawCircle(contact.end.x, contact.end.y, 5, PINK);
            }
        }

        DrawText(TextFormat("FPS: %.2f", 1.0f / GetFrameTime()), 80, 80, 16, WHITE);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}