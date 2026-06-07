#pragma once
#include "vec2.h"
#include <map>
#include "objects.h"

extern int countBox;

class Field;
class Points;

class Box {
public:
	bool userWin = false;

	std::map<int,BoxCollider> coordinates;
	std::map<int, bool> boxDown;

	void setCoordinates();
	void drawBox();
	void getFinish(Points& p);
};
