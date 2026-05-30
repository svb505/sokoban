#include <GLFW/glfw3.h>
#include "vec2.h"
#include <map>
#include "texture.h"
#include "box.h"
#include "getRandom.h"
#include "field.h"
#include "points.h"
#include "returnFromJson.h"

const int countBox = 4;

void Box::getFinish(Points& p) {
	for (int i = 0; i < countBox; i++) {
		for (auto c : p.coordinates) {
			if (c.x == coordinates[i].pos.x && c.y == coordinates[i].pos.y) boxDown[i] = true;
		}
	}
}

void Box::setCoordinates() {
	std::vector<Vec2> buf = returnValueFromJson("maze.json", "boxes");

	for (int i = 0; i < buf.size();i++) {
		coordinates[i] = { buf[i],20.0f };
	}

}
void Box::drawBox() {
	glEnable(GL_TEXTURE_2D);
	GLuint boxTex = 0;
	float h = 40.0f * 0.5f;

	for (auto c : coordinates) {
		if (boxDown[c.first]) boxTex = allTextures["boxF"];
		else boxTex = allTextures["box"];

		glBindTexture(GL_TEXTURE_2D, boxTex);

		glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(c.second.pos.x, c.second.pos.y, 0.0f);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-h, -h);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(h, -h);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(h, h);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-h, h);

		glEnd();
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);
}