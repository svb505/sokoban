#include "player.h"
#include <GLFW/glfw3.h>
#include <cmath>

void Player::draw(){
    const int segments = 64;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(collider.pos.x, collider.pos.y);

    for (int i = 0; i <= segments; i++){
        float angle = 2.0f * 3.1415926f * i / segments;

        float x = collider.pos.x + collider.radius * cos(angle);
        float y = collider.pos.y + collider.radius * sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}