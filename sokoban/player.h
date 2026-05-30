#pragma once
#include "vec2.h"
#include "objects.h"

class Player {
public:
	Circle collider = { {20.0f,20.0f},15.0f };

	void draw();
};