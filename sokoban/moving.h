#pragma once
#include "vec2.h"
#include <vector>
#include "objects.h"
#include <map>

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

Vec2 getDirectionOffset(Direction dir, float speed);
bool circleBoxCollision(const Circle& c, const BoxCollider& b);
bool checkCircleWallCollision(const Circle& player, const Wall& wall);
bool checkBoxWallCollision(const BoxCollider& box, const Wall& wall);
bool canMoveCircle(const Circle& player, const std::vector<Wall>& walls);
bool canMoveBox(const BoxCollider& box, const std::vector<Wall>& walls);
void tryMovePlayer(Circle& player, std::map<int, BoxCollider>& boxes, const std::vector<Wall>& walls,
    const std::vector<Wall>& wallsPerimetr,std::map<int, bool>& boxDown,Direction dir, float speed);