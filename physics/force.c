#include "raylib.h"
#include "force.h"

Vector2 Force_newGravityForce(float ms) {
    Vector2 gravity = Vector2Zero();

    gravity.x = 0;
    gravity.y = ms;
    
    return gravity;
}

Vector2 Force_newDragForce(Vector2 velocity, float k) {
    Vector2 dragForce = Vector2Zero(); 

    if(Vector2LengthSqr(velocity) > 0) {
        Vector2 dragDir = Vector2Scale(Vector2Normalize(velocity), -1);
        float dragMag = k * Vector2LengthSqr(velocity);

        dragForce = Vector2Scale(dragDir, dragMag);
    }

    return dragForce;
}

Vector2 Force_newSpringForce(Vector2 position, Vector2 anchor, float restLength, float k) {
    // direction from anchor do extremity
    Vector2 dist = Vector2Subtract(position, anchor);

    // the displacement (spring length - restLength)
    float disp = Vector2Length(dist) - restLength;

    Vector2 springDirection = Vector2Normalize(dist);
    float springMag = -k * disp;

    Vector2 springForce = Vector2Scale(springDirection, springMag);

    return springForce;
}

void Force_springDraw(Vector2 position, Vector2 anchor, float restLength, float k) {
    Vector2 dist = Vector2Subtract(position, anchor);
    float disp = Vector2Length(dist) - restLength;

    if(disp < -1) {
    DrawLine(anchor.x, anchor.y, position.x, position.y, YELLOW);
    } else if(disp > -1 && disp < 1) {
    DrawLine(anchor.x, anchor.y, position.x, position.y, GREEN);
    } else {
    DrawLine(anchor.x, anchor.y, position.x, position.y, PURPLE);
    }
}