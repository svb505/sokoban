#pragma once
#include "vec2.h"

struct Circle {
    Vec2 pos;
    float radius;
};

struct BoxCollider {
    Vec2 pos;
    float halfSize;
};
struct Wall {
    Vec2 start;
    Vec2 end;
};