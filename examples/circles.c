#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#include "physics/body.h"
#include "physics/force.h"
#include "physics/collision.h"
#include "graphics/graphics.h"

const int screenWidth = 800;
const int screenHeight = 600;

const float radius = 20.0f;
Body circleWall[71] = {0};
Body circles[100] = {0};

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    for (int i = 0; i < 20; i++)
    {
        circleWall[i] = Body_new(i * 40, 0, 10.0f);
        Body_setShapeCircle(&circleWall[i], radius);
        circleWall[i].isStatic = true;
        circleWall[i].invMass = 0;
    }

    for (int i = 20; i < 40; i++)
    {
        circleWall[i] = Body_new((i - 20) * 40, 600, 10.0f);
        Body_setShapeCircle(&circleWall[i], radius);
        circleWall[i].isStatic = true;
        circleWall[i].invMass = 0;
    }

    for (int i = 40; i < 55; i++)
    {
        circleWall[i] = Body_new(0, (i - 40) * 40, 10.0f);
        Body_setShapeCircle(&circleWall[i], radius);
        circleWall[i].isStatic = true;
        circleWall[i].invMass = 0;
    }

    for (int i = 55; i < 71; i++)
    {
        circleWall[i] = Body_new(800, (i - 55) * 40, 10.0f);
        Body_setShapeCircle(&circleWall[i], radius);
        circleWall[i].isStatic = true;
        circleWall[i].invMass = 0;
    }

    for (int i = 0; i < 100; i++)
    {
        circles[i] = Body_new(GetRandomValue(0, 600) + 40, GetRandomValue(0, 500) + 40, 5.0f);
        Body_setShapeCircle(&circles[i], 10.0f);
        circles[i].restitution = 1.0;
    }

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        for (int i = 0; i < 100; i++)
        {
            Body_addForce(&circles[i], (Vector2){0, 9.8 * circles[i].mass});
            Body_integrate(&circles[i], deltaTime);
            Shape_update(circles[i].shape, circles[i].position, circles[i].rotation);
        }

        for (int i = 0; i < 71; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                CollisionContact contact;
                if (Physics_isCollidingCircleCircle(&circles[j], &circleWall[i], &contact))
                {
                    Physics_resolveCollision(&contact);
                }
            }
        }

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (i == j)
                    continue;

                CollisionContact contact;
                if (Physics_isCollidingCircleCircle(&circles[i], &circles[j], &contact))
                {
                    Physics_resolveCollision(&contact);
                }
            }
        }

        BeginDrawing();
        {
            ClearBackground(BLACK);

            for (int i = 0; i < 71; i++)
            {
                Body circle = circleWall[i];
                Graphics_drawCircle(circle.position, circle.shape->circle.radius, circle.rotation);
            }

            for (int i = 0; i < 100; i++)
            {
                Graphics_drawCircle(circles[i].position, circles[i].shape->circle.radius, circles[i].rotation);
            }
        }

        DrawText(TextFormat("FPS: %.2f", 1.0f/GetFrameTime()), 80, 80, 16, WHITE);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}