#include <GLFW/glfw3.h>
#include "vec2.h"
#include "getRandom.h"
#include <vector>
#include "points.h"
#include "field.h"
#include <fstream>

const int segments = 64;
const float radius = 6.0f;

void Points::draw() {
	glColor3f(1.0f, 0.0f, 1.0f);
	
	for (auto c : coordinates) {
		glBegin(GL_TRIANGLE_FAN);

		glVertex2f(c.x, c.y);

		for (int i = 0; i <= segments; i++) {
			float angle = 2.0f * 3.1415926f * i / segments;

			float x = c.x + radius * cos(angle);
			float y = c.y + radius * sin(angle);

			glVertex2f(x, y);
		}

		glEnd();
	}

}