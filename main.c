#include "raylib.h"
#include "raymath.h"

#include "physics/body.h"
#include "physics/force.h"

const int screenWidth = 800;
const int screenHeight = 600;

#define BODY_COUNT 362
Body bodies [BODY_COUNT];

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    int xi = 0;
    int yj = 50;
    for(int i=0; i<BODY_COUNT; i++) {
        xi+=50;
        if((xi+50) % screenWidth == 0) {
            xi = 50;
            yj+=50;
        }
        bodies[i] = NewBody(xi, yj, 0, 0, 5);
        bodies[i].shape = Shape_newCircle(20, i*DEG2RAD);
    }

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        for (int i = 0; i < BODY_COUNT; i++)
        {
            Body_addForce(&bodies[i], Force_newDragForce(bodies[i].velocity, 0.0001));
            // Body_addForce(&bodies[i], Force_newGravityForce(9.8));
            Body_integrate(&bodies[i], GetFrameTime());
        }


        BeginDrawing();
        {
            ClearBackground(BLACK);

            for (int i = 0; i < BODY_COUNT; i++)
            {
                Body_draw(&bodies[i]);
            }
        }
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}