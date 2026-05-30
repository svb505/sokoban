#pragma once
#include <vector>
#include "vec2.h"

class Field;

extern const int segments;
extern const float radius;

class Points {
public:
	std::vector<Vec2> coordinates;

	void draw();
};