#pragma once
#include "vec2.h"
#include <map>
#include "objects.h"

extern const int countBox;

class Field;
class Points;

class Box {
public:
	std::map<int,BoxCollider> coordinates;
	std::map<int, bool> boxDown;

	void setCoordinates();
	void drawBox();
	void getFinish(Points& p);
};
