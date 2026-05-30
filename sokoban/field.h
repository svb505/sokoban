#pragma once
#include <vector>
#include "vec2.h"
#include <map>
#include <random>
#include "objects.h"

extern float cellSize;

class Field {
private:
	void addWall(std::vector<Wall>& container,float x1,float y1,float x2,float y2);
public:
	Field(int EW, int EH);

	std::vector<Wall> verticlesBord;
	std::vector<Wall> verticlesLabirynt;

	void loadWallsToField(const std::string& path, std::vector<Wall>& verticlesLabirynt);
	void drawPerimetr();
	void setLabirynt(int EW, int EH);
	void drawLab();
	bool checkCollision(Vec2 player);
	void drawGrid(float minX, float maxX, float minY, float maxY);
};
