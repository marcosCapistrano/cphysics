#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#include "physics/body.h"
#include "physics/force.h"
#include "physics/collision.h"
#include "graphics/graphics.h"

const int screenWidth = 800;
const int screenHeight = 600;

Body body;
Body body2;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    body = Body_new(400, 500, 20.0f);
    Body_setShapeCircle(&body, 20.0f);

    body2 = Body_new(400, 200, 50.0f);
    Body_setShapeCircle(&body2, 50);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        Body_addForce(&body, (Vector2){0, 9.8 * body.mass});
        Body_addForce(&body, Force_newDragForce(body.velocity, 0.0001f));
        Body_addTorque(&body, 100.1f * body.mass);
        Body_integrate(&body, deltaTime);
        Shape_update(body.shape, body.position, body.rotation);

        Body_addForce(&body2, (Vector2){0, 9.8 * body2.mass});
        Body_addForce(&body2, Force_newDragForce(body2.velocity, 0.0001f));
        Body_addTorque(&body2, 100.1f * body2.mass);
        Body_integrate(&body2, deltaTime);
        Shape_update(body2.shape, body2.position, body2.rotation);

        if (body.position.y > screenHeight)
        {
            body.velocity.y = -body.velocity.y;
            body.position.y = screenHeight - 10;
        }

        if (body2.position.y > screenHeight)
        {
            body2.velocity.y = -body2.velocity.y;
            body2.position.y = screenHeight - 10;
        }

        CollisionContact contact;
        if (Physics_isCollidingCircleCircle(&body, &body2, &contact))
        {
            Physics_resolveCollision(&contact);
        }

        BeginDrawing();
        {
            ClearBackground(BLACK);

            Graphics_drawCircle(body.position, body.shape->circle.radius, body.rotation);
            Graphics_drawCircle(body2.position, body2.shape->circle.radius, body2.rotation);

            CollisionContact contact;
            if (Physics_isCollidingCircleCircle(&body, &body2, &contact))
            {
                DrawCircle(contact.start.x, contact.start.y, 5, RED);
                DrawCircle(contact.end.x, contact.end.y, 5, RED);

                printf("start: %f %f\n", contact.start.x, contact.start.y);
                printf("end: %f %f\n\n", contact.end.x, contact.end.y);

                DrawCircle(50, 50, 5, RED);
            }
        }
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}