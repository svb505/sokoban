#include <windows.h>
#include "field.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "vec2.h"
#include "text.h"
#include <string>
#include <sstream>
#include <random>
#include "texture.h"
#include <fstream>
#include <nlohmann//json.hpp>

using json = nlohmann::json;

float cellSize = 40.0f;

void Field::loadWallsToField(const std::string& path,std::vector<Wall>& verticlesLabirynt){
	std::ifstream file(path);

	if (!file.is_open()) return;

	json root;

	file >> root;

	for (auto& wall : root["walls"])
	{
		addWall(
			verticlesLabirynt,

			wall["x1"].get<float>(),
			wall["y1"].get<float>(),

			wall["x2"].get<float>(),
			wall["y2"].get<float>()
		);
	}
}
void Field::addWall(std::vector<Wall>& container,float x1,float y1,float x2,float y2) {
	container.push_back({{x1, y1},{x2, y2}});
}
void drawText(float x, float y, const std::string& text) {
	glRasterPos2f(x, y);

	for (char c : text) {
		wglUseFontBitmaps(wglGetCurrentDC(), c, 1, 1000 + c);
		glCallList(1000 + c);
	}
}

Field::Field(int EW, int EH) {
	addWall(verticlesBord,-(EW - 20.0f), EH - 10.0f,EW - 20.0f, EH - 10.0f);
	addWall(verticlesBord, EW - 20.0f, EH - 10.0f, EW - 20.0f, -(EH - 10.0f));
	addWall(verticlesBord, EW - 20.0f, -(EH - 10.0f), -(EW - 20.0f), -(EH - 10.0f));
	addWall(verticlesBord, -(EW - 20.0f), -(EH - 10.0f), -(EW - 20.0f), EH - 10.0f);
}
void Field::setLabirynt(int EW, int EH) {

	verticlesLabirynt.clear();

	float halfW = EW - 20.0f;
	float halfH = EH - 10.0f;

	addWall(verticlesLabirynt, -160.0f, 20.0f, -40.0f, 20.0f);
	addWall(verticlesLabirynt, 40.0f, 20.0f, halfW, 20.0f);

	addWall(verticlesLabirynt, 20.0f, 180.0f, 20.0f, 80.0f);

	addWall(verticlesLabirynt, -120.0f, -100.0f, -20.0f, -100.0f);
	addWall(verticlesLabirynt, 20.0f, 100.0f, 120.0f, 100.0f);

	addWall(verticlesLabirynt, -100.0f, 120.0f, -100.0f, 40.0f);
	addWall(verticlesLabirynt, 100.0f, -40.0f, 100.0f, -120.0f);
}
void Field::drawPerimetr() {
	glColor3f(1.0f,0.0f,0.0f);
	glLineWidth(7.0f);
	glBegin(GL_LINES);

	for (const Wall& wall : verticlesBord) {
		glVertex2f(wall.start.x, wall.start.y);
		glVertex2f(wall.end.x, wall.end.y);
	}

	glEnd();
}
void Field::drawLab() {
	glColor3f(1.0f, 0.5f, 0.0f);
	glLineWidth(5.0f);
	glBegin(GL_LINES);

	for (const Wall& wall : verticlesLabirynt) {
		glVertex2f(wall.start.x, wall.start.y);
		glVertex2f(wall.end.x, wall.end.y);
	}

	glEnd();
}
bool Field::checkCollision(Vec2 player) {
	return false;
}
void Field::drawGrid(float minX, float maxX, float minY, float maxY) {
	glColor4f(0.0f,1.0f,1.0f,0.3f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(0.01f);
	glBegin(GL_LINES);

	for (float x = minX; x < maxX; x += cellSize) {
		for (float y = minY; y < maxY; y += cellSize) {
			glVertex2f(x, y);
			glVertex2f(x + cellSize, y);

			glVertex2f(x + cellSize, y);
			glVertex2f(x + cellSize, y + cellSize);

			glVertex2f(x + cellSize, y + cellSize);
			glVertex2f(x, y + cellSize);

			glVertex2f(x, y + cellSize);
			glVertex2f(x, y);
		}
	}

	glEnd();
	glDisable(GL_BLEND);
}